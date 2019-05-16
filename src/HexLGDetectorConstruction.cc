#include "HexLGDetectorConstruction.hh"
#include "HexLGDetectorMessenger.hh"
#include "MaterialsHelper.hh"
#include "SurfacesHelper.hh"
#include "HexLGPMTSD.hh"
#include "StringManip.hh"
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

#include "G4SubtractionSolid.hh"
#include "G4Ellipsoid.hh"
#include "G4UnionSolid.hh"
#include "G4IntersectionSolid.hh"
#include "G4Cons.hh"
#include "G4Polyhedra.hh"
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

HexLGDetectorConstruction::HexLGDetectorConstruction()
: G4VUserDetectorConstruction()
{

  fGunPosX = 0.0;
  fGunPosY = 0.0;
  fDetectorMessenger = new HexLGDetectorMessenger(this);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HexLGDetectorConstruction::~HexLGDetectorConstruction() {
  delete fDetectorMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4VSolid* createOctagon(double height, double basesside_dia, double pmtside_dia, double wall_thick){

    double z_points[2];
    z_points[0]=0;
    z_points[1]=height;
    double zero_array[2]{0,0};

    double outerA_r[2];
    outerA_r[0]=basesside_dia*2./sqrt(2);
    outerA_r[1]=pmtside_dia/2.+wall_thick;

    double outerB_r[2];
    outerB_r[0]=basesside_dia;
    outerB_r[1]=pmtside_dia/2.+wall_thick;

    G4Polyhedra* outerA = new G4Polyhedra("outerA",0.25*M_PI,2*M_PI,6, 2, z_points, zero_array, outerA_r);
    G4Polyhedra* outerB = new G4Polyhedra("outerB",0*M_PI,2*M_PI,6, 2, z_points, zero_array, outerB_r);
    G4IntersectionSolid* outer_inter = new G4IntersectionSolid("theOctagon",outerA,outerB);

    double innerA_r[2];
    innerA_r[0]=basesside_dia*2./sqrt(2)-wall_thick;
    innerA_r[1]=pmtside_dia/2.;

    double innerB_r[2];
    innerB_r[0]=basesside_dia-wall_thick;
    innerB_r[1]=pmtside_dia/2.;

    double z_inn[2]{-0.1,height+0.1};

    G4Polyhedra* innerA = new G4Polyhedra("innerA",0.25*M_PI,2*M_PI,6, 2, z_inn, zero_array, innerA_r);
    G4Polyhedra* innerB = new G4Polyhedra("innerB",0*M_PI,2*M_PI,6, 2, z_inn, zero_array, innerB_r);
    G4IntersectionSolid* inner_inter = new G4IntersectionSolid("theOctagon",innerA,innerB);



    return new G4SubtractionSolid("theOctagon",outer_inter,inner_inter);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* HexLGDetectorConstruction::Construct(){

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
    //double oil_hlength = pmtbox_height-box_front_cap_thick; 
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

    G4double m_HexagoneRadius = 8.0*cm;

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
  G4Polyhedra *outer = new G4Polyhedra("volA",0, 360*deg,6,2, scint_z,  zero_array, m_HexagoneROuter);
  G4Polyhedra *inner = new G4Polyhedra("volB",0, 360*deg,6,2, scint_z,  zero_array, m_sepInside);  

  G4SubtractionSolid *sep_solid = new G4SubtractionSolid("sep_vol",outer,inner);

  //G4Polyhedra *sep_solid = new G4Polyhedra("sep_vol",0, 360*deg,6,2, scint_z,  m_sepInside, m_HexagoneROuter);
  G4LogicalVolume *sep_log = new G4LogicalVolume(sep_solid, Materials::FEP, "Sep_main_log");   
  G4PVPlacement *sep_phys = new G4PVPlacement(0,                       //no rotation
                    pos1,                    //at position
                    sep_log,             //its logical volume
                    "Separator_phys",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps); 
  //G4Polyhedra *core = new G4Polyhedra("SeparatorCore", 0, 360*deg,6,2, scint_z, zero_array, m_Envelope);
  //G4LogicalVolume* core_log = new G4LogicalVolume(core, Materials::CarbonFiber, "Separator_core");
  //new G4PVPlacement(NULL, {0,0,0},core_log,"Separator_core",sep_log,false, 0, true);  

  //new G4LogicalSkinSurface("SepOpticalSkin", core_log, SurfacesHelper::S().ESR);

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

   //new G4LogicalBorderSurface("SepOpticalBorderFEP", scint_phys, sep_phys, SurfacesHelper::S().FEP5mil);
   new G4LogicalBorderSurface("SepOpticalBorderFEP", scint_phys, sep_phys, SurfacesHelper::S().LUTtest);   

   G4Region* scvolregion = new G4Region("ScintVol");
   scvolregion->AddRootLogicalVolume(scint_log);

   //-------------------------------------------------------------  
   //Extra reflectors 
   //-------------------------------------------------------------    

   G4Polyhedra* extra_reflector = new G4Polyhedra("extra_reflector", 0, 360*deg, 6, 2, ref_z, zero_array, m_HexagoneROuter);
   G4Polyhedra* extra_reflector_inside = new G4Polyhedra("extra_reflector", 0, 360*deg, 6, 2, ref_z, zero_array, m_HexagoneROuterSmall);

   G4LogicalVolume* extra_reflector_log = new G4LogicalVolume(extra_reflector,Materials::PMMA,"extra_reflector_log");
   G4LogicalVolume* extra_reflector_inside_log = new G4LogicalVolume(extra_reflector_inside,Materials::PMMA,"extra_reflector_inside_log");

   G4PVPlacement* extra_reflector_phys_1 = 
   new G4PVPlacement(nullptr,G4ThreeVector(0,0,scint_height/2.),extra_reflector_log,"extra_reflector_phys",scint_log,false,0,true);

   G4PVPlacement* extra_reflector_phys_2 =
   new G4PVPlacement(nullptr,G4ThreeVector(0,0,-scint_height/2.- box_front_cap_thick),extra_reflector_log,"extra_reflector_phys",scint_log,false,0,true);   

   G4PVPlacement* extra_reflector_inside_phys = new G4PVPlacement(nullptr,{0,0,0},extra_reflector_inside_log,"extra_reflector_inside_phys",extra_reflector_log,false,0,true);
   new G4LogicalBorderSurface("extra_reflector_border_1",extra_reflector_inside_phys,extra_reflector_phys_1,SurfacesHelper::S().ESR);
   new G4LogicalBorderSurface("extra_reflector_border_2",extra_reflector_inside_phys,extra_reflector_phys_2,SurfacesHelper::S().ESR);   
   //new G4LogicalBorderSurface("extra_reflector_border",extra_reflector_inside_phys,extra_reflector_phys,SurfacesHelper::S().ESR);   

   //-------------------------------------------------------------
   // PMT housing
   //-------------------------------------------------------------  
    G4RotationMatrix* pmt_flip = new G4RotationMatrix();// = new G4RotationMatrix(rotRod);
    pmt_flip->rotateY(M_PI*rad); 

   G4Polyhedra* m_Hexagone_solid
       = new G4Polyhedra("pmt_housing", 0, 360*deg, 6, 2, pmt_z, zero_array, m_HexagoneROuter);
    
   G4LogicalVolume* m_Hexagone_log
       = new G4LogicalVolume(m_Hexagone_solid, Materials::PMMA_black,"PMT_main_log");      

  //for(unsigned int npm = 0; npm < 2; npm++){
//   if(npm==0)new G4PVPlacement(0,                       //no rotation
   new G4PVPlacement(0,                       //no rotation    
                     {0,0,scint_height/2. + box_front_cap_thick },                    //at position
                     m_Hexagone_log,             //its logical volume
                     "PMT_main_log",                //its name
//                     "PMT_main_log_"+to_str(npm+1),                //its name                     
                     logicWorld,                //its mother  volume
                     false,                   //no boolean operation
                     0,                       //copy number
                     checkOverlaps); 

   //----------------------------------------------------------------------------------------------------------------------
   // Oil volume
   //---------------------------------------------------------------------------------------------------------------------- 

   G4Polyhedra* oil_box = new G4Polyhedra("min_oil", 0, 360*deg, 6, 2, oil_z, zero_array, m_HexagoneROuterOil);
   G4LogicalVolume* oil_log = new G4LogicalVolume(oil_box, oil_or_scint,"oil_log");
   G4PVPlacement* oil_phys = new G4PVPlacement(nullptr,{0,0,0},oil_log,"oil_phys",m_Hexagone_log,false,0,true);
     //new G4LogicalBorderSurface("extra_reflector_border",oil_phys,extra_reflector_inside_phys,SurfacesHelper::S().ESR_warped);   
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
     
     new G4PVPlacement(nullptr, {0,0,0},pmt_vac_log, "PMT_vac_phys",pmt_glass_log,false,0,true);
     //new G4PVPlacement(nullptr, {0,0,0},pmt_vac_log, "PMT_vac_phys_2",pmt_glass_log,false,2,true);     


     G4Ellipsoid* photocathode_ellcut=new G4Ellipsoid("photocathode_ellcut",diameter/2-pmt_glass_thickness-photocathode_thickness,diameter/2-pmt_glass_thickness-photocathode_thickness,pmt_bulb_semiaxis-pmt_glass_thickness-photocathode_thickness,0,0);
     G4Tubs* photocathode_cylcut = new G4Tubs("photocathode_cylcut",0,photocathode_diameter/2.,10*m,0,2*M_PI);
     G4SubtractionSolid* photocathode_ell = new G4SubtractionSolid("photocathode_ell",pmt_vac_bulb,photocathode_ellcut);
     G4IntersectionSolid* photocathode = new G4IntersectionSolid("photocathode",photocathode_ell,photocathode_cylcut,0,G4ThreeVector(0,0,-10.*m));
      G4LogicalVolume* photocathode_log = new G4LogicalVolume(photocathode,Materials::Photocathode,"photocathode_log");
      new G4PVPlacement(nullptr,{0,0,0},photocathode_log,"photocathode_phys",pmt_vac_log,false,0,true);       
     

     //new G4PVPlacement(nullptr,{0,0,0},photocathode_log,"photocathode_phys_2",pmt_vac_log,false,2,true);     

     double reflector_pmtside_opening = 103.897*mm;

     //r^2/(diameter/2)^2 + h^2 / (semiaxis-glass)^2 =1
     //how far does the pmt glass go forward from the edge of the reflector?
     double pmt_bulge = pmt_bulb_semiaxis
     -sqrt((pmt_bulb_semiaxis)*(pmt_bulb_semiaxis)*(1.-reflector_pmtside_opening*reflector_pmtside_opening/(diameter)/(diameter)));

     //how far is the pmt glass from the front of the mineral oil?
     double pmt_glass_z_from_front= pmt_bulb_semiaxis+reflector_length-pmt_bulge;

     new G4PVPlacement(nullptr, G4ThreeVector(0,0,pmt_glass_z_from_front),pmt_glass_log, "PMT_glass_phys",oil_log,false,0,true);    
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
     new G4LogicalBorderSurface("reflector_border",oil_phys,reflector_phys,SurfacesHelper::S().ESR_warped);
   
   //----------------------------------------------------------------------------------------------------------------------


    // PMT SD Optical Surface Properties

     G4OpticalSurface* photonDetSurface = new G4OpticalSurface("PhotonDetSurface", unified, ground, dielectric_metal );

     G4MaterialPropertiesTable* photonDetSurfaceProperty = new G4MaterialPropertiesTable();

     G4double p_mppc[] = {2.0*eV, 3.47*eV};
     const G4int nbins = sizeof(p_mppc)/sizeof(G4double);
     //G4double refl_mppc[] = {1.0,1.0};
     //assert(sizeof(refl_mppc) == sizeof(p_mppc));
     G4double effi_mppc[] = {1, 1};
     assert(sizeof(effi_mppc) == sizeof(p_mppc));
     //G4double SpecularLobe2[] = {1.0,1.0};
     //assert(sizeof(SpecularLobe2) == sizeof(p_mppc));
     //G4double SpecularSpike2[] = {0.0, 0.0};
     //assert(sizeof(SpecularSpike2) == sizeof(p_mppc));
     //G4double Backscatter2[] = {0.0, 0.0};
     //assert(sizeof(Backscatter2) == sizeof(p_mppc));
 
     //photonDetSurfaceProperty->AddProperty("REFLECTIVITY",p_mppc,refl_mppc,nbins);
     photonDetSurfaceProperty->AddProperty("EFFICIENCY",p_mppc,effi_mppc,nbins);
     //photonDetSurfaceProperty->AddProperty("SPECULARLOBECONSTANT", p_mppc, SpecularLobe2, nbins);
     //photonDetSurfaceProperty->AddProperty("SPECULARSPIKECONSTANT", p_mppc, SpecularSpike2, nbins);
     //photonDetSurfaceProperty->AddProperty("BACKSCATTERCONSTANT", p_mppc, Backscatter2, nbins);

     photonDetSurface->SetMaterialPropertiesTable(photonDetSurfaceProperty);

     new G4LogicalSkinSurface("PhotonDetSurface",photocathode_log,photonDetSurface);
            
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HexLGDetectorConstruction::ConstructSDandField() {

  if (!fPmt_SD.Get()) {
     //Created here so it exists as pmts are being placed
     G4cout << "Construction /HexLGDet/pmtSD" << G4endl;
     //G4MultiFunctionalDetector* photocathode_MFD = new G4MultiFunctionalDetector("photocathodeMFD");     
     HexLGPMTSD* pmt_SD = new HexLGPMTSD("/HexLGDet/pmtSD");
     //photocathode_MFD->RegisterPrimitive(pmt_SD);
     fPmt_SD.Put(pmt_SD);

     //pmt_SD->InitPMTs(2); //let pmtSD know # of pmts
     //pmt_SD->SetPmtPositions(0.0, 0.0, 0.0);
   }
   G4SDManager::GetSDMpointer()->AddNewDetector(fPmt_SD.Get());
   //sensitive detector is not actually on the photocathode.
   //processHits gets done manually by the stepping action.
   //It is used to detect when photons hit and get absorbed&detected at the
   //boundary to the photocathode (which doesnt get done by attaching it to a
   //logical volume.
   //It does however need to be attached to something or else it doesnt get
   //reset at the begining of events

   SetSensitiveDetector("photocathode_log", fPmt_SD.Get(),true); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void HexLGDetectorConstruction::SetGunPosX(G4double ival)
{
  //if(ival < 1){
  //  G4cout << "\n ---> Warning for SetGunPosX: Not set!" << G4endl;
  //  return;
  //}
  fGunPosX = ival;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void HexLGDetectorConstruction::SetGunPosY(G4double ival)
{
  //if(ival < 1){
  //  G4cout << "\n ---> Warning for SetGunPosY: Not set!" << G4endl;
  //  return;
  //}
  fGunPosY = ival;
}
