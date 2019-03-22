/// \file MaterialsHelper.cc

#include "MaterialsHelper.hh"
#include "StringManip.hh"
#include <map>
using std::map;

#include <G4SystemOfUnits.hh>
#include <G4ios.hh>

namespace Materials {

    map<string, G4Material*> xmats;
    G4NistManager* nist = G4NistManager::Instance();
    double room_T = 293.15*kelvin;

    // natual isotopic composition elemental materials
    G4Material* nat_H  = nist->FindOrBuildMaterial("G4_H",  true);
    //nat_Li = nist->FindOrBuildMaterial("G4_Li", true); // different isotopic ratio defined below
    G4Material* nat_Be = nist->FindOrBuildMaterial("G4_Be", true);
    G4Material* nat_B  = nist->FindOrBuildMaterial("G4_B",  true);
    G4Material* nat_C  = nist->FindOrBuildMaterial("G4_C",  true);
    G4Material* nat_N  = nist->FindOrBuildMaterial("G4_N",  true);
    G4Material* nat_O  = nist->FindOrBuildMaterial("G4_O",  true);
    G4Material* nat_F  = nist->FindOrBuildMaterial("G4_F",  true);
    G4Material* nat_Al = nist->FindOrBuildMaterial("G4_Al", true);
    G4Material* nat_Si = nist->FindOrBuildMaterial("G4_Si", true);
    G4Material* nat_P  = nist->FindOrBuildMaterial("G4_P",  true);
    G4Material* nat_S  = nist->FindOrBuildMaterial("G4_S",  true);
    G4Material* nat_Cl = nist->FindOrBuildMaterial("G4_Cl", true);
    G4Material* nat_Ca = nist->FindOrBuildMaterial("G4_Ca", true);
    G4Material* nat_Mn = nist->FindOrBuildMaterial("G4_Mn", true);
    G4Material* nat_Fe = nist->FindOrBuildMaterial("G4_Fe", true);
    G4Material* nat_Gd = nist->FindOrBuildMaterial("G4_Gd", true);
    G4Material* nat_Cu = nist->FindOrBuildMaterial("G4_Cu", true);
    G4Material* nat_Zn = nist->FindOrBuildMaterial("G4_Zn", true);
    G4Material* nat_Cr = nist->FindOrBuildMaterial("G4_Cr", true);
    G4Material* nat_Mo = nist->FindOrBuildMaterial("G4_Mo", true);
    G4Material* nat_Pb = nist->FindOrBuildMaterial("G4_Pb", true);
    G4Material* nat_Xe = nist->FindOrBuildMaterial("G4_Xe", true);
    G4Material* nat_W  = nist->FindOrBuildMaterial("G4_W",  true);

    // Geant4 built-in predefined materials
    G4Material* Air =           nist->FindOrBuildMaterial("G4_AIR", true, true);
    G4Material* Water =         nist->FindOrBuildMaterial("G4_WATER", true, true);
    G4Material* Mylar =         nist->FindOrBuildMaterial("G4_MYLAR", true, true);
    //G4Material* PMMA =          nist->FindOrBuildMaterial("G4_PLEXIGLASS", true, true); // customized below for approximate thermal neutron properties
    //G4Material* Polyeth =       nist->FindOrBuildMaterial("G4_POLYETHYLENE", true, true); // customized below to respect room temperature settings
    G4Material* Polystyrene =   nist->FindOrBuildMaterial("G4_POLYSTYRENE", true, true);
    G4Material* PTFE =          nist->FindOrBuildMaterial("G4_TEFLON", true, true);
    G4Material* Pyrex =         nist->FindOrBuildMaterial("G4_Pyrex_Glass", true, true);
    G4Material* Concrete =      nist->FindOrBuildMaterial("G4_CONCRETE");

    // isotopically pure components
    G4Element* el6Li  = new G4Element("eleLi6", "Li6", 1);
    G4Isotope* isoLi6 = new G4Isotope("isoLi6", 3, 6, 6.015122*g/mole);
    G4Element* elLi7  = new G4Element("eleLi7", "Li7", 1);
    G4Isotope* isoLi7 = new G4Isotope("isoLi7", 3, 7, 7.01600455*g/mole);
    G4Element* el1H  =  new G4Element("eleH1", "H1", 1);
    G4Isotope* isoH1 =  new G4Isotope("isoH1", 1, 1, 1.00782504*g/mole);
    G4Element* el2H  =  new G4Element("eleH2", "H2", 1);
    G4Isotope* isoH2 =  new G4Isotope("isoH2", 1, 2, 2.01410178*g/mole);
    G4Element* el3He  = new G4Element("eleHe3", "He3", 1);
    G4Isotope* iso3He = new G4Isotope("isoHe3", 2, 3, 3.0160293*g/mole);
    // elements with neutron thermal scattering data, defined in G4ParticleHPThermalScatteringNames.cc
    G4Element* elH_Water = new G4Element("TS_H_of_Water", "H_WATER", 1.0, 1.0079*g/mole);
    G4Element* elH_Poly = new G4Element("TS_H_of_Polyethylene", "H_POLYETHYLENE", 1.0, 1.0079*g/mole);
    G4Element* elC_Graphite = new G4Element("TS_C_of_Graphite", "C_GRAPHITE", 6.0, 12.0107*g/mole);

    // custom defined materials: built in init_materials() below.
    G4Material* PMMA =          new G4Material("PMMA", 1.18*g/cm3, 3, kStateSolid, room_T);
    G4Material* Polyeth =       new G4Material("Polyeth", 0.94*g/cm3, 2, kStateSolid, room_T);
    G4Material* Li6 =           new G4Material("Lithium6", 1.0*g/cm3, 1, kStateSolid, room_T);
    G4Material* nat_Li =        new G4Material("nat_Li", 0.463*g/cm3, 2);
    G4Material* H1 =            new G4Material("Protonium", 1.0*g/cm3, 1, kStateSolid, room_T);
    G4Material* H2 =            new G4Material("Deuterium", 1.0*g/cm3, 1, kStateSolid, room_T);
    G4Material* Vacuum =        new G4Material("Vacuum", 2., 4.0026*g/mole, 1.e-25*g/cm3, kStateGas, 2.73*kelvin, 3.e-18*pascal);
    G4Material* MinOil =        new G4Material("Mineral Oil CH1.1", 0.877*g/cm3, 2, kStateLiquid, room_T);
    G4Material* PVT =           new G4Material("Polyvinyl Toluene", 1.023*g/cm3, 2, kStateSolid, room_T);
    G4Material* RawPsiCumene =  new G4Material("Pseudocumene", 0.88*g/cm3, 2, kStateLiquid, room_T);
    G4Material* UG_AB =         new G4Material("UG_AB", 0.98*g/cm3, 5, kStateLiquid, room_T);
    G4Material* EJ309 =         new G4Material("EJ309", 0.9781*g/cm3, 3, kStateLiquid, room_T);
    G4Material* PMMA_black =    nullptr; // build after fully defining PMMA
    G4Material* PMMA_white =    nullptr; // build after fully defining PMMA
    G4Material* PLA =           new G4Material("PLA", 1.3*g/cm3, 3, kStateSolid, room_T);
    G4Material* PEEK =          new G4Material("PEEK", 1.32*g/cm3, 3, kStateSolid, room_T);
    G4Material* CarbonFiber =   new G4Material("CarbonFiber", 1.88*g/cm3, 1, kStateSolid, room_T);
    G4Material* BPoly5 =        new G4Material("5wt% Borated Polyethylene", 0.94*g/cm3, 2, kStateSolid, room_T);
    G4Material* BPoly30 =       new G4Material("30wt% Borated Polyethylene", 0.94*g/cm3, 2, kStateSolid, room_T);
    G4Material* LiPoly =        new G4Material("5wt% Lithiated Polyethylene", 0.94*g/cm3, 2, kStateSolid, room_T);
    G4Material* SS444 =         new G4Material("SS444", 8.*g/cm3, 3, kStateSolid, room_T);
    G4Material* SteelA36 =      new G4Material("SteelA36", 7.8*g/cm3, 7, kStateSolid, room_T);
    G4Material* Quartz =        new G4Material("Quartz", 2.62*g/cm3, 2, kStateSolid, room_T);
    G4Material* Dirt =          new G4Material("Dirt", 1.52*g/cm3, 5, kStateSolid, room_T);
    G4Material* BoricAcid =     new G4Material("BoricAcid", 1.435*g/cm3, 3);
    G4Material* Lead_II_Acetate = new G4Material("Lead_II_Acetate", 3.25*g/cm3, 4);
    G4Material* Photocathode =  new G4Material("photocathode", 1.*g/cm3, 3);
    G4Material* Gd2O3 =         new G4Material("Gd2O3", 7.07*g/cm3, 2, kStateSolid, room_T);
    G4Material* FEP =           new G4Material("FEP", 2150*kg/m3, 2, kStateSolid,room_T);


    bool init_materials() {

        static bool is_initialized = false;
        if(is_initialized) {
            G4cout << "Materials already initialized; not repeating." << G4endl;
            return false;
        }
        is_initialized = true;

        G4cout << "Initializing materials..." << G4endl;

        G4int nAtoms = 0; // placeholder variable for assuring G4int type

        el6Li->AddIsotope(isoLi6,100.*perCent);
        elLi7->AddIsotope(isoLi7,100.*perCent);
        el1H->AddIsotope(isoH1,  100.*perCent);
        el2H->AddIsotope(isoH2,  100.*perCent);
        el3He->AddIsotope(iso3He,100.*perCent);

        Li6->AddElement(el6Li,100.*perCent);

        nat_Li->AddElement(el6Li,0.0811);
        nat_Li->AddElement(elLi7,1-0.0811);

        H1->AddElement(el1H,100.*perCent);

        H2->AddElement(el2H,100.*perCent);

        MinOil->AddElement(elC_Graphite, 91.53*perCent);
        MinOil->AddElement(elH_Water, 8.47*perCent);

        PVT->AddElement(elC_Graphite, 91.478*perCent);
        PVT->AddElement(elH_Poly, 8.522*perCent);

        RawPsiCumene->AddElement(elC_Graphite, 89.945*perCent);
        RawPsiCumene->AddElement(elH_Water, 10.055*perCent);

        UG_AB->AddElement(elC_Graphite, 76.3*perCent);
        UG_AB->AddElement(elH_Water,  9.7*perCent);
        UG_AB->AddElement(getEl("N"), 0.05*perCent);
        UG_AB->AddElement(getEl("O"), 13.8*perCent);
        UG_AB->AddElement(getEl("P"), 0.1*perCent);

        // (C_5 O_2 H_8)_n
        PMMA->AddElement(elC_Graphite, nAtoms = 5);
        PMMA->AddElement(getEl("O"), nAtoms = 2);
        PMMA->AddElement(elH_Poly, nAtoms = 8);

        // (C_2 H_4)_n
        Polyeth->AddElement(elC_Graphite, nAtoms = 2);
        Polyeth->AddElement(elH_Poly, nAtoms = 4);

        // (C_3 H_4 O_2)_n
        PLA->AddElement(elC_Graphite, nAtoms = 3);
        PLA->AddElement(getEl("O"), nAtoms = 2);
        PLA->AddElement(elH_Poly, nAtoms = 4);

        PMMA_black =    new G4Material("PMMA_black", PMMA->GetDensity(), PMMA);
        PMMA_white =    new G4Material("PMMA_white", PMMA->GetDensity(), PMMA);

        //old: from EJ309 datasheet: H:C = 1.25:1 atomic ratio
//        EJ309->AddElement(elH_Water, nAtoms = 5);
//        EJ309->AddElement(getEl("C"), nAtoms = 4);
        //EJ309->AddMaterial(nat_C, 90.578*perCent);
        //EJ309->AddMaterial(nat_H, 9.422*perCent);
        //from Minfang's "Best guess"
        EJ309->AddMaterial(nat_C, 84.14*perCent);
        EJ309->AddMaterial(nat_H, 9.52*perCent);
        EJ309->AddMaterial(nat_O, 6.34*perCent);

        // (O_3 C_19 H_12)_n
        PEEK->AddElement(elH_Poly, nAtoms = 12);
        PEEK->AddElement(getEl("C"), nAtoms = 19);
        PEEK->AddElement(getEl("O"), nAtoms = 3);

        CarbonFiber->AddElement(elC_Graphite, nAtoms=1);

        BPoly5->AddMaterial(Polyeth, 95.0*perCent);
        BPoly5->AddMaterial(nat_B,   5.0*perCent);

        BPoly30->AddMaterial(Polyeth, 70.0*perCent);
        BPoly30->AddMaterial(nat_B,   30.0*perCent);

        LiPoly->AddMaterial(Polyeth, 95.0*perCent);
        LiPoly->AddMaterial(nat_Li,  5.0*perCent);

        SS444->AddMaterial(nat_Fe, 80.*perCent);
        SS444->AddMaterial(nat_Cr, 18.*perCent);
        SS444->AddMaterial(nat_Mo, 2.*perCent);

        SteelA36->AddMaterial(nat_C,  0.27*perCent);
        SteelA36->AddMaterial(nat_Cu, 0.20*perCent);
        SteelA36->AddMaterial(nat_Fe, 98.13*perCent); // extra 0.13 brings total sum to 1
        SteelA36->AddMaterial(nat_Mn, 1.03*perCent);
        SteelA36->AddMaterial(nat_P,  0.04*perCent);
        SteelA36->AddMaterial(nat_Si, 0.28*perCent);
        SteelA36->AddMaterial(nat_S,  0.05*perCent);

        Quartz->AddMaterial(nat_Si, 0.4674);
        Quartz->AddMaterial(nat_O,  0.5326);

        /*
        Concrete = new G4Material("Concrete", 2.3*g/cm3, 6, kStateSolid, room_T);
        Concrete->AddMaterial(nat_Si, 0.227915);
        Concrete->AddMaterial(nat_O, 0.60541);
        Concrete->AddMaterial(nat_H, 0.09972);
        Concrete->AddMaterial(nat_Ca, 0.04986);
        Concrete->AddMaterial(nat_Al, 0.014245);
        Concrete->AddMaterial(nat_Fe, 0.00285);
        */

        Dirt->AddElement(getEl("C"),  nAtoms=  1);
        Dirt->AddElement(getEl("Si"), nAtoms= 29);
        Dirt->AddElement(getEl("Al"), nAtoms= 15);
        Dirt->AddElement(getEl("Fe"), nAtoms=  5);
        Dirt->AddElement(getEl("O"),  nAtoms= 50);

        BoricAcid->AddElement(getEl("B"), nAtoms= 1);
        BoricAcid->AddElement(getEl("O"), nAtoms= 3);
        BoricAcid->AddElement(getEl("H"), nAtoms= 3);

        Lead_II_Acetate->AddElement(getEl("Pb"),nAtoms= 1);
        Lead_II_Acetate->AddElement(getEl("C"), nAtoms= 4);
        Lead_II_Acetate->AddElement(getEl("H"), nAtoms= 6);
        Lead_II_Acetate->AddElement(getEl("O"), nAtoms= 4);

        Photocathode->AddElement(getEl("Sb"), nAtoms = 1);
        Photocathode->AddElement(getEl("Rb"), nAtoms = 1);
        Photocathode->AddElement(getEl("Cs"), nAtoms = 1);

        Gd2O3->AddElement(getEl("Gd"), nAtoms=2);
        Gd2O3->AddElement(getEl("O"), nAtoms=3);

        FEP->AddMaterial(nat_F,8./13.);
        FEP->AddMaterial(nat_C,5./13.);


        setupOptical();

        // pre-build some materials for availability in named materials catalog
        get6LiLS(EJ309, 0.001);
        get6LiLS(EJ309, 0.00077, true, 10*0.00077/0.001, "AD1_Scint");
        getBoratedH2O(0.02);
        getBoratedH2O(0.05);

        return true;
    }

    G4Element* getEl(const string& name) {
        return G4NistManager::Instance()->FindOrBuildElement(name);
    }

    G4Material* getBoratedH2O(double loading) {
        if(!loading) return Water;
        string mnm = "H2O_"+to_str(100*loading)+"wt%_Boron";
        if(!xmats.count(mnm)) {
            G4Material* BW = new G4Material(mnm.c_str(), Water->GetDensity(), 2, Water->GetState(), Water->GetTemperature());
            const double massratio = (3*(15.999+1.008)+10.81)/10.81; // ratio of boric acid mass to boron mass
            BW->AddMaterial(Water, 1.-loading*massratio);
            BW->AddMaterial(BoricAcid, loading*massratio);
            xmats[mnm] = BW;
        }
        return xmats[mnm];
    }

    G4Material* get6LiLS(G4Material* base, double loading, bool enriched, double LiClMolarity, string mnm) {
        if(!loading || !base) return base;

        if(!mnm.size()) {
            mnm = base->GetName()+string("-")+to_str(100*loading)+(enriched?"wt%-6Li":"wt%-Li");
            if(LiClMolarity != 8.) mnm += "-" + to_str(LiClMolarity)+"molar";
        }

        if(!xmats.count(mnm)) {
            G4cout << "Bulding 6Li-loaded (" << loading*100 << "% by weight) scintillator " << mnm << " ...\n";
            G4Material* myLi = enriched? Li6 : nat_Li;

            G4Material* Li_mat = nullptr;
            double avgLiA = enriched? 6.02 : 0.075*6.02 + .925*7.02;        // Li average mass
            double m_Cl = loading*35.45/avgLiA;                             // mass fraction Cl (for equal LiCl mixture), by ratio of masses to Li
            double m_H2O = (1000./LiClMolarity - avgLiA -35.45)/avgLiA*loading;   // mass fraction H2O for LiCl solution

            Li_mat = new G4Material(mnm.c_str(), base->GetDensity(), 4, base->GetState(), base->GetTemperature());
            Li_mat->AddMaterial(UG_AB, 1.-loading-m_Cl-m_H2O);
            Li_mat->AddMaterial(myLi, loading);
            Li_mat->AddMaterial(nat_Cl, m_Cl);
            Li_mat->AddMaterial(Water, m_H2O);

            Li_mat->SetMaterialPropertiesTable(base->GetMaterialPropertiesTable());
            Li_mat->GetIonisation()->SetBirksConstant(base->GetIonisation()->GetBirksConstant());

            xmats[mnm] = Li_mat;

        }
        return xmats[mnm];
    }

    G4Material* get3He(double dens) {
        const string mnm = "3He_" + to_str(dens/(mg/cm3)) + "_mg/cm3";
        if(!xmats.count(mnm)) {
            G4Material* He3gas = new G4Material(mnm.c_str(), dens, 1, kStateGas, room_T);
            He3gas->AddElement(el3He,2);
            xmats[mnm] = He3gas;
        }
        return xmats[mnm];
    }

    void setupOptical() {

        G4cout << "Setting material optical properties..." << G4endl;

        // NOTE: The emission spectra had to be modified from manufaturer specifications
        //       as the Scintillation process samples the photon energy uniformly in photon energy
        //       (rather than wavelength), which translates to 1/x^2 in wavelength. This
        //       was found to distort the emission spectrum when converted back to wavelengths, so a factor
        //       of x^2 was applied to the listed distribution to counter this effect.

        // table of photon energies, for wavelengths 520 nm to 360 nm in 2 nm steps
        const G4int nEntries = 81;
        G4double PhotonEnergy[nEntries];
        for(int i=0; i<nEntries; i++) {
            G4double l = (520-2*i)*nm;
            PhotonEnergy[i] = CLHEP::h_Planck * CLHEP::c_light / l;
        }

        /////////////////////////////////////////
        // Gd-Loaded Liquid Pseudocumene - BC-525

        // Refractive Index
        G4double RIndexPC[nEntries];
        for(int i = 0; i < nEntries; i++) RIndexPC[i] = 1.57;
        G4double RayleighLengthPC[nEntries];
        for (int i = 0; i < nEntries; i++) RayleighLengthPC[i] = 1.*m;
        // Absorption Length
        G4double AbsLengthPC[nEntries] = {
            10.*m, 10.*m, 10.*m, 10.*m, 10.*m, 10.*m, 10.*m, 10.*m, 10.*m,
            10.*m, 10.*m, 10.*m, 10.*m, 10.*m, 10.*m, 10.*m, 10.*m, 10.*m,
            10.*m, 10.*m, 10.*m, 10.*m, 10.*m, 10.*m, 10.*m, 10.*m, 10.*m,
            10.*m, 10.*m, 10.*m, 10.*m, 10.*m, 10.*m, 10.*m, 10.*m, 10.*m,
            10.*m, 10.*m, 10.*m, 10.*m, 10.*m, 10.*m, 10.*m, 10.*m, 10.*m,
            10.*m, 10.*m, 10.*m, 10.*m, 10.*m, 10.*m, 10.*m, 10.*m, 10.*m,
            10.*m, 10.*m, 10.*m, 10.*m, 10.*m, 10.*m, 10.*m, 10.*m, 10.*m,
            10.*m, 10.*m, 10.*m, 9.4*m, 8.7*m, 8.0*m, 7.3*m, 6.7*m, 6.2*m,
            5.7*m, 5.3*m, 4.9*m, 4.5*m, 4.2*m, 3.9*m, 3.7*m, 3.5*m, 3.3*m
        };

        // Scintillation - Fast Component - Double Modified Spectrum
        G4double ScintFastPC[nEntries] = {
            0.036, 0.042, 0.047, 0.054, 0.062, 0.070, 0.078, 0.087, 0.096,
            0.105, 0.115, 0.124, 0.133, 0.142, 0.152, 0.162, 0.173, 0.183,
            0.194, 0.205, 0.218, 0.231, 0.245, 0.261, 0.281, 0.305, 0.338,
            0.370, 0.402, 0.439, 0.469, 0.493, 0.515, 0.537, 0.559, 0.580,
            0.602, 0.629, 0.677, 0.787, 0.885, 0.939, 0.972, 0.993, 1.004,
            1.000, 0.984, 0.952, 0.909, 0.862, 0.801, 0.744, 0.669, 0.601,
            0.526, 0.455, 0.401, 0.351, 0.299, 0.254, 0.208, 0.173, 0.146,
            0.122, 0.104, 0.090, 0.079, 0.070, 0.062, 0.056, 0.051, 0.046,
            0.041, 0.037, 0.033, 0.029, 0.026, 0.023, 0.021, 0.019, 0.018
        };

        G4MaterialPropertiesTable* mptCumene = new G4MaterialPropertiesTable();

        // Specification of properties that are constant with photon energy
        mptCumene->AddConstProperty("FASTTIMECONSTANT", 3.8*ns);            // Fast Component Decay Time
        //  mptCumene->AddConstProperty("SLOWTIMECONSTANT",20.0*ns);        // Slow Component Decay Time
        mptCumene->AddConstProperty("YIELDRATIO",1.0);                      // 1 = all fast, 0 = all slow, fractional yield ratio allowed
        mptCumene->AddConstProperty("SCINTILLATIONYIELD",9000./MeV);        // Physical value for scintillation yield for Psuedocumene
        mptCumene->AddConstProperty("RESOLUTIONSCALE",1.0);                 // Standard deviation on scintillation yield number

        // Specification of properties that vary with photon energy - linearly interpolated
        mptCumene->AddProperty("FASTCOMPONENT", PhotonEnergy, ScintFastPC, nEntries);       // Light Yield for Fast Component
        //  mptCumene->AddProperty("SLOWCOMPONENT", PhotonEnergy, ScintSlowPC, nEntries);   // Light Yield for Slow Component
        mptCumene->AddProperty("RINDEX", PhotonEnergy, RIndexPC, nEntries);                 // Refractive Index of Material
        mptCumene->AddProperty("ABSLENGTH", PhotonEnergy, AbsLengthPC, nEntries);           // Abosrption Length of Material
        mptCumene->AddProperty("RAYLEIGH",PhotonEnergy, RayleighLengthPC, nEntries);      // Rayleigh scattering length of material.

        RawPsiCumene->SetMaterialPropertiesTable(mptCumene);
        RawPsiCumene->GetIonisation()->SetBirksConstant(0.1*mm/MeV);

        ////////////////////////
        UG_AB->GetIonisation()->SetBirksConstant(0.1*mm/MeV); // TODO

        ////////////////////////
        EJ309->GetIonisation()->SetBirksConstant(0.1*mm/MeV); // TODO
        EJ309->SetMaterialPropertiesTable(mptCumene); // TODO

        //////////////////////////////////////////////////////////////////
        // Anthracene-doped Polyvinyltoluene Plastic Scintillator - EJ-500

        G4double RIndexPVT[nEntries];
        for(int i = 0; i < nEntries; i++) RIndexPVT[i] = 1.58;

        G4double AbsLengthPVT[nEntries];
        for(int i = 0; i < nEntries; i++) AbsLengthPVT[i] = 5.*m;

        // Scintillation - Fast Component
        G4double ScintFastPVT[nEntries] = {
            0.015, 0.019, 0.025, 0.031, 0.036, 0.043, 0.050, 0.058, 0.066,
            0.074, 0.083, 0.092, 0.102, 0.112, 0.121, 0.132, 0.147, 0.161,
            0.178, 0.201, 0.222, 0.249, 0.278, 0.312, 0.344, 0.377, 0.410,
            0.437, 0.463, 0.483, 0.504, 0.522, 0.544, 0.564, 0.585, 0.608,
            0.630, 0.658, 0.695, 0.743, 0.789, 0.840, 0.880, 0.924, 0.956,
            0.983, 0.999, 1.000, 0.981, 0.932, 0.860, 0.693, 0.515, 0.406,
            0.337, 0.273, 0.193, 0.118, 0.072, 0.040, 0.018, 0.009, 0.005,
            0.004, 0.003, 0.002, 0.001, 0.000, 0.000, 0.000, 0.000, 0.000,
            0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000
        };

        G4MaterialPropertiesTable* mptToluene = new G4MaterialPropertiesTable();// Generates new material properties table for scintillator
        mptToluene->AddConstProperty("FASTTIMECONSTANT", 2.1*ns);               // Fast Component Decay Time
        //  mptToluene->AddConstProperty("SLOWTIMECONSTANT",20.0*ns);           // Slow Component Decay Time
        mptToluene->AddConstProperty("YIELDRATIO",1.0);                         // 1 = all fast, 0 = all slow, fractional yield ratio allowed
        mptToluene->AddConstProperty("SCINTILLATIONYIELD",10000./MeV);          // Physical value for scintillation yield for Polyvinyltoluene
        mptToluene->AddConstProperty("RESOLUTIONSCALE",1.0);                    // Standard deviation on scintillation yield number

        mptToluene->AddProperty("FASTCOMPONENT", PhotonEnergy, ScintFastPVT, nEntries);         // Light Yield for Fast Component
        //  mptToluene->AddProperty("SLOWCOMPONENT", PhotonEnergy, ScintSlowPVT, nEntries);     // Light Yield for Slow Component
        mptToluene->AddProperty("RINDEX", PhotonEnergy, RIndexPVT, nEntries);                   // Refractive Index of Material
        mptToluene->AddProperty("ABSLENGTH", PhotonEnergy, AbsLengthPVT, nEntries);             // Abosrption Length of Material

        PVT->SetMaterialPropertiesTable(mptToluene);
        PVT->GetIonisation()->SetBirksConstant(0.2*mm/MeV);

        /////////////////////
        // Plexiglass Windows

        G4double RIndex_PMMA[nEntries];
        for(int i = 0; i < nEntries; i++) RIndex_PMMA[i] = 1.492;

        G4double AbsLength_PMMA[nEntries] = {
            0.5*m, 0.5*m, 0.5*m, 0.5*m, 0.5*m, 0.5*m, 0.5*m, 0.5*m, 0.5*m,
            0.5*m, 0.5*m, 0.5*m, 0.5*m, 0.5*m, 0.5*m, 0.5*m, 0.5*m, 0.5*m,
            0.5*m, 0.5*m, 0.5*m, 0.5*m, 0.5*m, 0.5*m, 0.5*m, 0.5*m, 0.5*m,
            0.5*m, 0.5*m, 0.5*m, 0.5*m, 0.5*m, 0.5*m, 0.5*m, 0.5*m, 0.5*m,
            0.5*m, 0.5*m, 0.5*m, 0.5*m, 0.5*m, 0.5*m, 0.5*m, 0.5*m, 0.5*m,
            0.5*m, 0.5*m, 0.5*m, 0.5*m, 0.5*m, 0.5*m, 0.5*m, 0.5*m, 0.5*m,
            0.5*m, 0.5*m, 0.5*m, 0.5*m, 0.5*m, 0.5*m, 0.5*m, 0.5*m, 0.4*m,
            0.3*m, 0.2*m, 0.16*m, 0.13*m, 0.10*m, 0.075*m, 0.055*m, 0.04*m, 0.032*m,
            0.024*m, 0.018*m, 0.014*m, 0.01*m, 8.*mm, 6.*mm, 4.*mm, 2.*mm, 0.1*mm

        };

        G4MaterialPropertiesTable* mptPMMA = new G4MaterialPropertiesTable();
        mptPMMA->AddProperty("RINDEX", PhotonEnergy, RIndex_PMMA, nEntries);
        mptPMMA->AddProperty("ABSLENGTH", PhotonEnergy, AbsLength_PMMA, nEntries);

        PMMA->SetMaterialPropertiesTable(mptPMMA);

        G4double Ephoton2[2] = { 1.5*eV, 6.0*eV };
        G4double AbsLength_Black[2] = { 0.01*mm, 0.01*mm };
        G4MaterialPropertiesTable* mptPMMA_blk = new G4MaterialPropertiesTable();
        mptPMMA_blk->AddProperty("RINDEX", PhotonEnergy, RIndex_PMMA, nEntries);
        mptPMMA_blk->AddProperty("ABSLENGTH", Ephoton2, AbsLength_Black, 2);
        PMMA_black->SetMaterialPropertiesTable(mptPMMA_blk);

        G4double AbsLength_Photocathode[2] = {551*nm,138*nm};
        //G4double AbsLength_Photocathode[2] = {1e-5*nm,1e-5*nm};
        G4double RIndex_Photocathode[2]={2.7,2.7};
        //G4double RIndex_Photocathode[2]={1.49,1.49};
        G4MaterialPropertiesTable* mptPhotocathode = new G4MaterialPropertiesTable();
        mptPhotocathode->AddProperty("RINDEX",Ephoton2,RIndex_Photocathode,2);
        mptPhotocathode->AddProperty("ABSLENGTH",Ephoton2,AbsLength_Photocathode,2);
        Photocathode->SetMaterialPropertiesTable(mptPhotocathode);

        //////////////
        // Mineral Oil

        G4double RIndex3[nEntries];
        for(int i = 0; i < nEntries; i++) RIndex3[i] = 1.48;
        G4double AbsLength3[nEntries];
        for(int i = 0; i < nEntries; i++) AbsLength3[i] = 4.*m;

        G4MaterialPropertiesTable* mptOil = new G4MaterialPropertiesTable();
        mptOil->AddProperty("RINDEX", PhotonEnergy, RIndex3, nEntries);
        mptOil->AddProperty("ABSLENGTH", PhotonEnergy, AbsLength3, nEntries);

        MinOil->SetMaterialPropertiesTable(mptOil);

        //////
        // Air

        G4double RIndex4[nEntries];
        for(int i = 0; i < nEntries; i++) RIndex4[i] = 1.000293;
        G4double AbsLength4[nEntries];
        for(int i = 0; i < nEntries; i++) AbsLength4[i] = 50.*m;

        G4MaterialPropertiesTable* mptAir = new G4MaterialPropertiesTable();
        mptAir->AddProperty("RINDEX", PhotonEnergy, RIndex4, nEntries);
        mptAir->AddProperty("ABSLENGTH", PhotonEnergy, AbsLength4, nEntries);

        Air->SetMaterialPropertiesTable(mptAir);

        /////////
        // Vacuum

        G4double RIndex5[nEntries];
        for(int i = 0; i < nEntries; i++) RIndex5[i] = 1.00;
        G4MaterialPropertiesTable* mptVacuum = new G4MaterialPropertiesTable();
        mptVacuum->AddProperty("RINDEX", PhotonEnergy, RIndex5, nEntries);

        Vacuum->SetMaterialPropertiesTable(mptVacuum);

        /////////
        // Quartz

        G4double RIndex6[nEntries];
        for(int i = 0; i < nEntries; i++) RIndex6[i] = 1.46;
        G4double AbsLengthQu[nEntries];
        for(int i = 0; i < nEntries; i++) AbsLengthQu[i] = 0.001*mm;

        G4MaterialPropertiesTable* mptQuartz = new G4MaterialPropertiesTable();
        mptQuartz->AddProperty("RINDEX", PhotonEnergy, RIndex6, nEntries);
        mptQuartz->AddProperty("ABSLENGTH", PhotonEnergy, AbsLengthQu, nEntries);

        Quartz->SetMaterialPropertiesTable(mptQuartz);

        /////////
        // FEP
        G4double RIndex7[nEntries];
        for(int i = 0; i < nEntries; i++) RIndex7[i] = 1.344;//via Xianyi

        //        from xianyi:
        //        Wavelengths	360	365	370	375	380	385	390	395	400	405	410	415	420	425	430	435	440	445	450	455	460	465	470	475	480	485	490	495	500	505	510	515	520	525	530	535	540	545	550
        //5milFEP(Trans)	0.853	0.854	0.852	0.847	0.851	0.857	0.858	0.857	0.863	0.862	0.867	0.871	0.873	0.878	0.877	0.879	0.88	0.885	0.885	0.888	0.89	0.891	0.894	0.896	0.895	0.899	0.9	0.903	0.905	0.906	0.909	0.909	0.912	0.913	0.915	0.918	0.919	0.92	0.92
        vector<double> PhotonEnergyExtended39;
        for (double wl = 550*nm; wl>= 360*nm; wl-=5*nm) {
            PhotonEnergyExtended39.push_back(CLHEP::h_Planck * CLHEP::c_light / wl);
        }
        vector<double> PhotonEnergyExtended20;
        for (double wl = 550*nm; wl>= 360*nm; wl-=10*nm) {
            PhotonEnergyExtended20.push_back(CLHEP::h_Planck * CLHEP::c_light / wl);
        }
//        vector<double> FEP5mil_trans ={0.853,0.854,0.852,0.847,0.851,0.857,0.858,0.857,0.863,0.862,0.867,0.871,0.873,0.878,0.877,0.879,0.88,0.885,0.885,0.888,0.89,0.891,0.894,0.896,0.895,0.899,0.9,0.903,0.905,0.906,0.909,0.909,0.912,0.913,0.915,0.918,0.919,0.92,0.92};
        vector<double> FEP5mil_trans ={0.7,0.8,0.9577464789,0.9673913043,0.9789473684,0.9791666667,0.9793814433,0.9793814433,0.9896907216,0.9896907216,0.9896907216,0.9795918367,0.9897959184,0.9897959184,0.9897959184,0.9897959184,0.9897959184,0.9897959184,0.9896907216,0.9896907216};
        vector<double> FEP5mil_refl = { 0.01,0.02,0.06,0.08,0.1,0.09,0.09,0.08,0.08,0.07,0.07,0.07,0.06,0.06,0.06,0.05,0.06,0.06,0.05,0.05};

        for (uint i = 0; i<FEP5mil_trans.size();i++){
//            FEP5mil_trans[i] += FEP5mil_refl[i];
            FEP5mil_trans[i] = std::min<double>(FEP5mil_trans[i],.99999999);

        }
        for (uint i = 0; i<FEP5mil_refl.size();i++){
            FEP5mil_refl[i]*=1.;
        }

        std::reverse(FEP5mil_trans.begin(),FEP5mil_trans.end());
        std::reverse(FEP5mil_refl.begin(),FEP5mil_refl.end());
        vector<double> FEP_abs_length;
        vector<double> FEP_ray_length;
        for (auto trans : FEP5mil_trans){
            double abs_len = -0.010*2.54*cm / std::log(trans);
            FEP_abs_length.push_back(abs_len*1.);
        }
        for (auto refl : FEP5mil_refl){
            double ray_len = -0.01*2.54*cm / std::log(1-refl);
            FEP_ray_length.push_back(ray_len);
        }

        G4MaterialPropertiesTable* mptFEP = new G4MaterialPropertiesTable();
        mptFEP->AddProperty("RINDEX", PhotonEnergy, RIndex7, nEntries);
        mptFEP->AddProperty("ABSLENGTH", PhotonEnergyExtended20.data(), FEP_abs_length.data(), PhotonEnergyExtended20.size());
//        mptFEP->AddProperty("RAYLEIGH", PhotonEnergyExtended20.data(), FEP_ray_length.data(), PhotonEnergyExtended20.size());


        FEP->SetMaterialPropertiesTable(mptFEP);

    }
}