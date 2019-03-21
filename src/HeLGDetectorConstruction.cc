#include "HeLGDetectorConstruction.hh"
#include "MaterialsHelper.hh"
#include "SurfacesHelper.hh"
//#include "LXePMTSD.hh"
//#include "LXeScintSD.hh"
//#include "LXeDetectorMessenger.hh"
//#include "LXeMainVolume.hh"
//#include "LXeWLSSlab.hh"

#include "G4SDManager.hh"
#include "G4RunManager.hh"

#include "G4GeometryManager.hh"
#include "G4SolidStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"

#include "G4OpticalSurface.hh"
#include "G4MaterialTable.hh"
#include "G4VisAttributes.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "globals.hh"
#include "G4UImanager.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HeLGDetectorConstruction::HeLGDetectorConstruction()
: G4VUserDetectorConstruction()//fLXe_mt(nullptr), fMPTPStyrene(nullptr)
{
  /*fExperimentalHall_box = nullptr;
  fExperimentalHall_log = nullptr;
  fExperimentalHall_phys = nullptr;

  fLXe = fAl = fAir = fVacuum = fGlass = nullptr;
  fPstyrene = fPMMA = fPethylene1 = fPethylene2 = nullptr;

  fN = fO = fC = fH = nullptr;

  fSaveThreshold = 0;
  SetDefaults();

  DefineMaterials();
  fDetectorMessenger = new HeLGDetectorMessenger(this);*/

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HeLGDetectorConstruction::~HeLGDetectorConstruction() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4VSolid* createTuncatedCone(double height, double basesside_dia, double pmtside_dia, double wall_thick, G4VSolid* container_box, G4double* zero_array, G4double* m_HexagoneROuterOil){

    double r2min = pmtside_dia/2.;
    double r2max = r2min+wall_thick;
//    double r1max = 10.02*cm;
//    double r1max = 100.2453272393947;
    double r1max = 100.2568742447785;        
    double r1min = r1max-wall_thick;
    G4Cons* cone = new G4Cons("cone",r1min,r1max,r2min,r2max,height/2.,0,2.*M_PI);

//    G4IntersectionSolid* truncated_cone = new G4IntersectionSolid("truncated_cone",cone,container_box);

    double rect_outer[6];//{basesside_dia,basesside_dia};
    double rect_inner[6];//{basesside_dia-wall_thick,basesside_dia-wall_thick};
    double rect_z[2]{0,-height};

    size_t i;
    for (i=0; i<6; i++) 
    {
      rect_outer[i] = m_HexagoneROuterOil[i]; 
      rect_inner[i] = m_HexagoneROuterOil[i] - wall_thick; 
    }
    G4Polyhedra* sides = new G4Polyhedra("sides",0.,2.*M_PI,6,2,rect_z,rect_inner,rect_outer);

    //return new G4UnionSolid("trunccone_sides",sides,cone,nullptr,G4ThreeVector(0,0,-height/2.));
    return new G4IntersectionSolid("truncated_cone",new G4UnionSolid("trunccone_sides",sides,cone,nullptr,G4ThreeVector(0,0,-height/2.)),container_box);    

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* HeLGDetectorConstruction::Construct(){

  //if (fExperimentalHall_phys) { return fExperimentalHall_phys; }

  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  Materials::init_materials();
   
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  G4ThreeVector pos1 = G4ThreeVector(0, 0, 0);
  //     
  // World
  //

  G4double world_sizeXY = 300*cm;
  G4double world_sizeZ  = 300*cm;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");  

  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       world_sizeXY, world_sizeXY, world_sizeZ);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking

  logicWorld->SetVisAttributes(G4VisAttributes::GetInvisible());

 //-------------------------------------------------------------
  // Define your variables here
  //-------------------------------------------------------------
    double scint_height = 117.6*cm;
    double box_front_cap_thick = 1.27*cm;
    double box_side_wall_thick = 0.3175*cm;
    double pmtbox_height = 34.924*cm;
    double oil_hlength = pmtbox_height-box_front_cap_thick; 
    double sepThick = 0.0465*25.4*mm;  
    double envelope_thick = 0.002*25.4*mm; 

    double scint_z[2]{-scint_height/2.,scint_height/2.};
    double zero_array[2]{0,0};
    double ref_z[2]{0,box_front_cap_thick};
    double pmt_z[2]{0, pmtbox_height};
    double oil_z[2]{0,pmtbox_height - box_front_cap_thick};

    G4double m_HexagoneROuter[6];
    G4double m_HexagoneROuterOil[6];    
    G4double m_HexagoneROuterSmall[6];
    G4double m_sepInside[6];
    G4double m_Envelope[6];

    G4double m_HexagoneRadius = 9*cm;

    G4ThreeVector dim = G4ThreeVector(14.47, 14.47, 34.924);

    G4Material* oil_or_scint=Materials::MinOil;



    //-------------------------------------------------------------
    // Hexagon volume variables
    //-------------------------------------------------------------    

    size_t i;
    for (i=0; i<6; i++) 
    {
      m_HexagoneROuterOil[i] = m_HexagoneRadius-box_side_wall_thick ;
      m_HexagoneROuter[i] = m_HexagoneRadius;
      m_HexagoneROuterSmall[i] = m_HexagoneRadius-.1*mm;
      m_sepInside[i] = m_HexagoneRadius- sepThick;
      m_Envelope[i] = m_sepInside[i] + envelope_thick;
    }
  //-------------------------------------------------------------
  // Container/Separator
  //-------------------------------------------------------------   
  G4Polyhedra *sep_solid = new G4Polyhedra("sep_vol",0, 360*deg,6,2, scint_z,  m_sepInside, m_HexagoneROuter);
  G4LogicalVolume *sep_log = new G4LogicalVolume(sep_solid, Materials::FEP, "Sep_main_log");   
  G4PVPlacement *sep_phys = new G4PVPlacement(0,                       //no rotation
                    pos1,                    //at position
                    sep_log,             //its logical volume
                    "Separator_phys",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps); 
  G4Polyhedra *core = new G4Polyhedra("SeparatorCore", 0, 360*deg,6,2, scint_z, zero_array, m_Envelope);
  G4LogicalVolume* core_log = new G4LogicalVolume(core, Materials::CarbonFiber, "Separator_core");
  new G4PVPlacement(NULL, {0,0,0},core_log,"Separator_core",sep_log,false, 0, true);

  new G4LogicalSkinSurface("SepOpticalSkin", core_log, SurfacesHelper::S().ESR);

  //-------------------------------------------------------------
  // Scintillator Volume
  //-------------------------------------------------------------  

   G4Polyhedra *scint_solid = new G4Polyhedra("scint_vol",0, 360*deg,6,2, scint_z,  zero_array, m_sepInside);
   G4LogicalVolume *scint_log = new G4LogicalVolume(scint_solid, Materials::get6LiLS(Materials::EJ309, 0.00077, true, 10*0.00077/0.001), "Scint_main_log");   
   G4PVPlacement *scint_phys =  new G4PVPlacement(0,                       //no rotation
                     pos1,                    //at position
                     scint_log,             //its logical volume
                     "SCINT_phys",                //its name
                     logicWorld,                //its mother  volume
                     false,                   //no boolean operation
                     0,                       //copy number
                     checkOverlaps); 

   new G4LogicalBorderSurface("SepOpticalBorderFEP", scint_phys, sep_phys, SurfacesHelper::S().FEP5mil);

   G4Region* scvolregion = new G4Region("ScintVol");
   scvolregion->AddRootLogicalVolume(scint_log);

   //-------------------------------------------------------------  
   //Extra reflectors 
   //-------------------------------------------------------------    

   G4Polyhedra* extra_reflector = new G4Polyhedra("extra_reflector", 0, 360*deg, 6, 2, ref_z, zero_array, m_HexagoneROuter);
   G4Polyhedra* extra_reflector_inside = new G4Polyhedra("extra_reflector", 0, 360*deg, 6, 2, ref_z, zero_array, m_HexagoneROuterSmall);

   G4LogicalVolume* extra_reflector_log = new G4LogicalVolume(extra_reflector,Materials::PMMA,"extra_reflector_log");
   G4LogicalVolume* extra_reflector_inside_log = new G4LogicalVolume(extra_reflector_inside,Materials::PMMA,"extra_reflector_inside_log");

   G4PVPlacement* extra_reflector_phys_1 = new G4PVPlacement(nullptr,G4ThreeVector(0,0,scint_height/2.),extra_reflector_log,"extra_reflector_phys_1",scint_log,false,1,true);
   G4PVPlacement* extra_reflector_inside_phys_1 = new G4PVPlacement(nullptr,{0,0,0},extra_reflector_inside_log,"extra_reflector_inside_phys_1",extra_reflector_log,false,1,true);
   new G4LogicalBorderSurface("extra_reflector_border_1",extra_reflector_inside_phys_1,extra_reflector_phys_1,SurfacesHelper::S().ESR);

   G4PVPlacement* extra_reflector_phys_2 = new G4PVPlacement(nullptr,G4ThreeVector(0,0,-scint_height/2.- box_front_cap_thick),extra_reflector_log,"extra_reflector_phys_2",scint_log,false,2,true);
   G4PVPlacement* extra_reflector_inside_phys_2 = new G4PVPlacement(nullptr,{0,0,0},extra_reflector_inside_log,"extra_reflector_inside_phys_2",extra_reflector_log,false,2,true);
   new G4LogicalBorderSurface("extra_reflector_border_2",extra_reflector_inside_phys_2,extra_reflector_phys_2,SurfacesHelper::S().ESR);

   //-------------------------------------------------------------
   // PMT housing
   //-------------------------------------------------------------  
    G4RotationMatrix* pmt_flip = new G4RotationMatrix();// = new G4RotationMatrix(rotRod);
    pmt_flip->rotateY(M_PI*rad); 

   G4Polyhedra* m_Hexagone_solid
       = new G4Polyhedra("pmt_housing", 0, 360*deg, 6, 2, pmt_z, zero_array, m_HexagoneROuter);
    
   G4LogicalVolume* m_Hexagone_log
       = new G4LogicalVolume(m_Hexagone_solid, Materials::PMMA_black,"PMT_main_log");      

    new G4PVPlacement(0,                       //no rotation
                     {0,0,scint_height/2. + box_front_cap_thick },                    //at position
                     m_Hexagone_log,             //its logical volume
                     "PMT_main_log_1",                //its name
                     logicWorld,                //its mother  volume
                     false,                   //no boolean operation
                     1,                       //copy number
                     checkOverlaps); 
    new G4PVPlacement(pmt_flip,                       //no rotation
                     {0,0,-scint_height/2.-box_front_cap_thick },                    //at position
                     m_Hexagone_log,             //its logical volume
                     "PMT_main_log_2",                //its name
                     logicWorld,                //its mother  volume
                     false,                   //no boolean operation
                     2,                       //copy number
                     checkOverlaps);
  
   //----------------------------------------------------------------------------------------------------------------------
   // Oil volume
   //---------------------------------------------------------------------------------------------------------------------- 

   G4Polyhedra* oil_box = new G4Polyhedra("min_oil", 0, 360*deg, 6, 2, oil_z, zero_array, m_HexagoneROuterOil);
   G4LogicalVolume* oil_log = new G4LogicalVolume(oil_box, oil_or_scint,"oil_log");
   G4PVPlacement* oil_phys_1 = new G4PVPlacement(nullptr,{0,0,0},oil_log,"oil_phys",m_Hexagone_log,false,1,true);
   //G4PVPlacement* oil_phys_2 = new G4PVPlacement(nullptr,{0,0,0},oil_log,"oil_phys",m_Hexagone_log,false,2,true);   
  
   //----------------------------------------------------------------------------------------------------------------------
   // Photocatode/Bulb
   //----------------------------------------------------------------------------------------------------------------------
     double diameter = 12.7*cm;
     double reflector_length = 2.54*cm;
     double pmt_bulb_semiaxis = 44.79 *mm;//extracted from scale(?) drawing
     double pmt_stem_length = 4*cm+pmt_bulb_semiaxis/2.;//measured from center of ellipsoidal bulb
     double pmt_stem_diameter = 84.5*mm;
     double pmt_glass_thickness = 2*mm;//??
     double photocathode_diameter = 110*mm;//Diameter of circle, not of sphere PCath lies on
     double photocathode_thickness = 0.01*mm;

     G4Ellipsoid* pmt_bulb=new G4Ellipsoid("pmt_bulb", diameter/2.,diameter/2., pmt_bulb_semiaxis,0,0);
     G4Tubs* pmt_stem=new G4Tubs("pmt_stem", 0, pmt_stem_diameter/2., pmt_stem_length/2., 0, 2.*M_PI);
     G4UnionSolid* pmt_glass=new G4UnionSolid("pmt_glass",pmt_bulb,pmt_stem,nullptr,G4ThreeVector(0,0,pmt_stem_length/2.));
     G4LogicalVolume* pmt_glass_log = new G4LogicalVolume(pmt_glass, Materials::PMMA,"PMT_glass_log");
//     //placed in a few more lines

     G4Ellipsoid* pmt_vac_bulb=new G4Ellipsoid("pmt_vac_bulb", diameter/2.-pmt_glass_thickness,diameter/2.-pmt_glass_thickness, pmt_bulb_semiaxis-pmt_glass_thickness,0,0);
     G4Tubs* pmt_vac_stem=new G4Tubs("pmt_vac_stem", 0, pmt_stem_diameter/2.-pmt_glass_thickness, pmt_stem_length/2.-pmt_glass_thickness, 0, 2.*M_PI);
     G4UnionSolid* pmt_vac=new G4UnionSolid("pmt_glass",pmt_vac_bulb,pmt_vac_stem,nullptr,G4ThreeVector(0,0,pmt_stem_length/2.+pmt_glass_thickness));
     G4LogicalVolume* pmt_vac_log = new G4LogicalVolume(pmt_vac, Materials::Vacuum,"PMT_vac_log");
     
     new G4PVPlacement(nullptr, {0,0,0},pmt_vac_log, "PMT_vac_phys",pmt_glass_log,false,1,true);
     //new G4PVPlacement(nullptr, {0,0,0},pmt_vac_log, "PMT_vac_phys_2",pmt_glass_log,false,2,true);     


     G4Ellipsoid* photocathode_ellcut=new G4Ellipsoid("photocathode_ellcut",diameter/2-pmt_glass_thickness-photocathode_thickness,diameter/2-pmt_glass_thickness-photocathode_thickness,pmt_bulb_semiaxis-pmt_glass_thickness-photocathode_thickness,0,0);
     G4Tubs* photocathode_cylcut = new G4Tubs("photocathode_cylcut",0,photocathode_diameter/2.,10*m,0,2*M_PI);
     G4SubtractionSolid* photocathode_ell = new G4SubtractionSolid("photocathode_ell",pmt_vac_bulb,photocathode_ellcut);
     G4IntersectionSolid* photocathode = new G4IntersectionSolid("photocathode",photocathode_ell,photocathode_cylcut,0,G4ThreeVector(0,0,-10.*m));
     G4LogicalVolume* photocathode_log = new G4LogicalVolume(photocathode,Materials::Photocathode,"photocathode_log");
     
     new G4PVPlacement(nullptr,{0,0,0},photocathode_log,"photocathode_phys",pmt_vac_log,false,1,true);
     //new G4PVPlacement(nullptr,{0,0,0},photocathode_log,"photocathode_phys_2",pmt_vac_log,false,2,true);     

     double reflector_pmtside_opening = 103.897*mm;

     //r^2/(diameter/2)^2 + h^2 / (semiaxis-glass)^2 =1
     //how far does the pmt glass go forward from the edge of the reflector?
     double pmt_bulge = pmt_bulb_semiaxis
     -sqrt((pmt_bulb_semiaxis)*(pmt_bulb_semiaxis)*(1.-reflector_pmtside_opening*reflector_pmtside_opening/(diameter)/(diameter)));

     //how far is the pmt glass from the front of the mineral oil?
     double pmt_glass_z_from_front= pmt_bulb_semiaxis+reflector_length-pmt_bulge;

     new G4PVPlacement(nullptr, G4ThreeVector(0,0,pmt_glass_z_from_front),pmt_glass_log, "PMT_glass_phys",oil_log,false,1,true);    
     //new G4PVPlacement(nullptr, G4ThreeVector(0,0,-pmt_glass_z_from_front),pmt_glass_log, "PMT_glass_phys_2",oil_log,false,2,true);         

   //----------------------------------------------------------------------------------------------------------------------
   // Reflector
   //----------------------------------------------------------------------------------------------------------------------
     G4VSolid* reflector;


     //double reflector_z_offset = 0;
     reflector = createOctagon(reflector_length,m_HexagoneRadius - box_side_wall_thick,reflector_pmtside_opening,3.303*mm);
   
     //reflector = createTuncatedCone(reflector_length,m_HexagoneRadius - box_side_wall_thick,reflector_pmtside_opening,0.01*mm,oil_box, zero_array, m_HexagoneROuterOil);
     G4LogicalVolume* reflector_log = new G4LogicalVolume(reflector,Materials::Mylar,"reflector_log");


     G4PVPlacement* reflector_phys=new G4PVPlacement(nullptr,G4ThreeVector(0,0,0),reflector_log,"reflector_phys",oil_log,false,0,true);
     new G4LogicalBorderSurface("reflector_border",oil_phys_1,reflector_phys,SurfacesHelper::S().ESR_warped);

   //----------------------------------------------------------------------------------------------------------------------

     //G4MultiFunctionalDetector* photocathode_MFD = new G4MultiFunctionalDetector("photocathodeMFD");
     //PhotoMultiplierScorer* photocathode_PMScorer = new PhotoMultiplierScorer("photocathodeScorer",4);
     //photocathode_MFD->RegisterPrimitive(photocathode_PMScorer);
     //G4SDManager::GetSDMpointer()->AddNewDetector(photocathode_MFD);
     //photocathode_log->SetSensitiveDetector(photocathode_MFD);                     



  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HeLGDetectorConstruction::ConstructSDandField() {

  //if (!fMainVolume) return;

  // PMT SD

  // if (!fPmt_SD.Get()) {
  //   //Created here so it exists as pmts are being placed
  //   G4cout << "Construction /LXeDet/pmtSD" << G4endl;
  //   LXePMTSD* pmt_SD = new LXePMTSD("/LXeDet/pmtSD");
  //   fPmt_SD.Put(pmt_SD);

  //   pmt_SD->InitPMTs((fNx*fNy+fNx*fNz+fNy*fNz)*2); //let pmtSD know # of pmts
  //   pmt_SD->SetPmtPositions(fMainVolume->GetPmtPositions());
  // }
  // G4SDManager::GetSDMpointer()->AddNewDetector(fPmt_SD.Get());
  // //sensitive detector is not actually on the photocathode.
  // //processHits gets done manually by the stepping action.
  // //It is used to detect when photons hit and get absorbed&detected at the
  // //boundary to the photocathode (which doesnt get done by attaching it to a
  // //logical volume.
  // //It does however need to be attached to something or else it doesnt get
  // //reset at the begining of events

  // SetSensitiveDetector(fMainVolume->GetLogPhotoCath(), fPmt_SD.Get());

  // // Scint SD

  // if (!fScint_SD.Get()) {
  //   G4cout << "Construction /LXeDet/scintSD" << G4endl;
  //   LXeScintSD* scint_SD = new LXeScintSD("/LXeDet/scintSD");
  //   fScint_SD.Put(scint_SD);
  // }
  // G4SDManager::GetSDMpointer()->AddNewDetector(fScint_SD.Get());
  // SetSensitiveDetector(fMainVolume->GetLogScint(), fScint_SD.Get());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// void LXeDetectorConstruction::SetDimensions(G4ThreeVector dims) {
//   fScint_x=dims[0];
//   fScint_y=dims[1];
//   fScint_z=dims[2];
//   G4RunManager::GetRunManager()->ReinitializeGeometry();
// }
 
// //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// void LXeDetectorConstruction::SetHousingThickness(G4double d_mtl) {
//   fD_mtl=d_mtl;
//   G4RunManager::GetRunManager()->ReinitializeGeometry();
// }

// //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// void LXeDetectorConstruction::SetNX(G4int nx) {
//   fNx=nx;
//   G4RunManager::GetRunManager()->ReinitializeGeometry();
// }

// //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// void LXeDetectorConstruction::SetNY(G4int ny) {
//   fNy=ny;
//   G4RunManager::GetRunManager()->ReinitializeGeometry();
// }

// //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// void LXeDetectorConstruction::SetNZ(G4int nz) {
//   fNz=nz;
//   G4RunManager::GetRunManager()->ReinitializeGeometry();
// }

// //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// void LXeDetectorConstruction::SetPMTRadius(G4double outerRadius_pmt) {
//   fOuterRadius_pmt=outerRadius_pmt;
//   G4RunManager::GetRunManager()->ReinitializeGeometry();
// }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HeLGDetectorConstruction::SetDefaults() {

  //TODO : Add hard-coded values here

  //Resets to default values
  // fD_mtl=0.0635*cm;

  // fScint_x = 17.8*cm;
  // fScint_y = 17.8*cm;
  // fScint_z = 22.6*cm;

  // fNx = 2;
  // fNy = 2;
  // fNz = 3;

  // fOuterRadius_pmt = 2.3*cm;

  // fSphereOn = true;
  // fRefl = 1.0;

  // fNfibers = 15;
  // fWLSslab = false;
  // fMainVolumeOn = true;
  // fMainVolume = nullptr;
  // fSlab_z = 2.5*mm;

  // G4UImanager::GetUIpointer()
  //   ->ApplyCommand("/LXe/detector/scintYieldFactor 1.");

  // if(fLXe_mt)fLXe_mt->AddConstProperty("SCINTILLATIONYIELD",12000./MeV);
  // if(fMPTPStyrene)fMPTPStyrene->AddConstProperty("SCINTILLATIONYIELD",10./keV);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//void LXeDetectorConstruction::SetSphereOn(G4bool b) {
//  fSphereOn=b;
//  G4RunManager::GetRunManager()->ReinitializeGeometry();
//}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//void LXeDetectorConstruction::SetHousingReflectivity(G4double r) {
//  fRefl=r;
//  G4RunManager::GetRunManager()->ReinitializeGeometry();
//}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// void LXeDetectorConstruction::SetWLSSlabOn(G4bool b) {
//   fWLSslab=b;
//   G4RunManager::GetRunManager()->ReinitializeGeometry();
// }

// //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// void LXeDetectorConstruction::SetMainVolumeOn(G4bool b) {
//   fMainVolumeOn=b;
//   G4RunManager::GetRunManager()->ReinitializeGeometry();
// }

// //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// void LXeDetectorConstruction::SetNFibers(G4int n) {
//   fNfibers=n;
//   G4RunManager::GetRunManager()->ReinitializeGeometry();
// }

// //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// void LXeDetectorConstruction::SetMainScintYield(G4double y) {
//   fLXe_mt->AddConstProperty("SCINTILLATIONYIELD",y/MeV);
// }

// //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
// void LXeDetectorConstruction::SetWLSScintYield(G4double y) {
//   fMPTPStyrene->AddConstProperty("SCINTILLATIONYIELD",y/MeV);
// }

// //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// void LXeDetectorConstruction::SetSaveThreshold(G4int save){
// /*Sets the save threshold for the random number seed. If the number of photons
// generated in an event is lower than this, then save the seed for this event
// in a file called run###evt###.rndm
// */
//   fSaveThreshold=save;
//   G4RunManager::GetRunManager()->SetRandomNumberStore(true);
// }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......