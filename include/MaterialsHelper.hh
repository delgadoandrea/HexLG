/// \file MaterialsHelper.hh Materials definitions used in detector geometries.
#ifndef MATERIALSHELPER_HH
/// Assure this header is loaded only once
#define MATERIALSHELPER_HH

#include <string>
using std::string;

#include <G4Material.hh>
#include <G4NistManager.hh>
#include <G4MaterialPropertiesTable.hh>

/// Namespace for pre-defined materials
namespace Materials {

    extern G4NistManager* nist;         ///< NIST materials DB
    extern double room_T;               ///< materials "room temperature"

    extern G4Element* el6Li;            ///< pure 6Li
    extern G4Element* el3He;            ///< pure 3He
    extern G4Element* el1H;             ///< pure 1H
    extern G4Element* el2H;             ///< pure 2H

    extern G4Material* nat_H;           ///< natural hydrogen
    extern G4Material* nat_Li;          ///< natural lithium
    extern G4Material* Li6;             ///< isotopically pure 6Li
    extern G4Material* H1;              ///< isotopically pure 1H
    extern G4Material* H2;              ///< isotopically pure 2H
    extern G4Material* nat_Be;          ///< natural beryllium
    extern G4Material* nat_B;           ///< natural boron
    extern G4Material* nat_C;           ///< natural carbon
    extern G4Material* nat_N;           ///< natural nitrogen
    extern G4Material* nat_O;           ///< natural oxygen
    extern G4Material* nat_F;           ///< natural fluorine
    extern G4Material* nat_Al;          ///< natural aluminum
    extern G4Material* nat_Si;          ///< natural silicon
    extern G4Material* nat_P;           ///< natural phosphorus
    extern G4Material* nat_S;           ///< natural sulfur
    extern G4Material* nat_Cl;          ///< natural chlorine
    extern G4Material* nat_Ca;          ///< natural calcium
    extern G4Material* nat_Mn;          ///< natural manganese
    extern G4Material* nat_Fe;          ///< natural iron
    extern G4Material* nat_Gd;          ///< natural gadolinium
    extern G4Material* nat_Cu;          ///< natural copper
    extern G4Material* nat_Zn;          ///< natural zinc
    extern G4Material* nat_Cr;          ///< natural chromium
    extern G4Material* nat_Mo;          ///< natural molybdenum
    extern G4Material* nat_Pb;          ///< natural lead
    extern G4Material* nat_Xe;          ///< natural xenon
    extern G4Material* nat_W;           ///< natural tungsten

    extern G4Material* Vacuum;          ///< vacuum
    extern G4Material* Air;             ///< room air
    extern G4Material* MinOil;          ///< Mineral oil
    extern G4Material* Mylar;           ///< Mylar
    extern G4Material* PMMA;            ///< plexiglass, transparent
    extern G4Material* PMMA_black;      ///< plexiglass, black
    extern G4Material* PMMA_white;      ///< plexiglass, white
    extern G4Material* PEEK;            ///< PEEK (O_3 C_19 H_12)_n
    extern G4Material* CarbonFiber;     ///< Carbon fiber, currently pure carbon with reasonable density
    extern G4Material* Polyeth;         ///< Polyethylene (C_2 H_4)_n
    extern G4Material* PLA;             ///< Polylactic acid (C_3 H_4 O_2)_n, common 3D printing feedstock
    extern G4Material* Polystyrene;     ///< Polystyrene
    extern G4Material* PTFE;            ///< PTFE (Teflon)
    extern G4Material* BPoly5;          ///< Borated (5% by mass) polyethylene
    extern G4Material* BPoly30;         ///< Borated (30% by mass) polyethylene
    extern G4Material* LiPoly;          ///< Lithiated (5% by mass) polyethlyene
    extern G4Material* Water;           ///< Water
    extern G4Material* PVT;             ///< Polyvinyl Toluene scintillator
    extern G4Material* RawPsiCumene;    ///< un-doped pseudocumene scintillator base
    extern G4Material* UG_AB;           ///< Ultima Gold AB scintillator
    extern G4Material* EJ309;           ///< Eljen EJ-309 liquid scintillator
    extern G4Material* SS444;           ///< Stainless Steel 444
    extern G4Material* SteelA36;        ///< A36 mild steel
    extern G4Material* Quartz;          ///< Quartz
    extern G4Material* Pyrex;           ///< Pyrex borosilicate glass
    extern G4Material* Concrete;        ///< Concrete
    extern G4Material* Dirt;            ///< "Dirt,"  From PNNL-20401
    extern G4Material* BoricAcid;       ///< anhydrous boric acid B(OH)_3
    extern G4Material* Lead_II_Acetate; ///< anhydrous Pb(CH_3COO)_2
    extern G4Material* Photocathode;    ///< photocathode with special optical properties
    extern G4Material* Gd2O3;           ///< Gadolinium(III) oxide, neutron capture agent
    extern G4Material* FEP;           ///< FEP, flourinated plastic for reflector envelopes

    /// get 6Li-loaded version of scintillator (option for natural or enriched 6Li, and LiCl + H2O solution molarity)
    G4Material* get6LiLS(G4Material* base, double loading, bool enriched = true, double LiClMolarity = 8, string mnm = "");
    /// get boric acid loaded water
    G4Material* getBoratedH2O(double loading);
    /// get 3He gas at specified density
    G4Material* get3He(double dens);
    /// shortcut to get named G4Element
    G4Element* getEl(const string& name);

    /// initialize materials
    bool init_materials();
    /// set up material optical properties
    void setupOptical();
}


#endif
