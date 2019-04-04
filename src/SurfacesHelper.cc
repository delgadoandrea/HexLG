/// \file SurfacesHelper.cc

#include "SurfacesHelper.hh"
#include "StringManip.hh"

#include <G4SystemOfUnits.hh>
#include <G4ios.hh>
#include <G4MaterialPropertiesTable.hh>
#include <CLHEP/Units/PhysicalConstants.h>

SurfacesHelper* SurfacesHelper::theSurfHelper = nullptr;

SurfacesHelper& SurfacesHelper::S() {
    if(!theSurfHelper) theSurfHelper = new SurfacesHelper;
    return *theSurfHelper;
}

double wl2E(double wl){
    return CLHEP::h_Planck * CLHEP::c_light / (wl);
}

void init_array_flat(G4double* array, double value, size_t n){
    for(size_t i=0;i<n;i++){
        array[i]=value;
    }
}

SurfacesHelper::SurfacesHelper() {
    
    G4cout << "Initializing Surfaces" << G4endl;
    
    SolarMirror=new G4OpticalSurface("solarmirror_surf");
    {
        G4OpticalSurface* surf = SolarMirror;
        const G4int nE = 20;                         // Edit: number of photon energies to specify

        G4double WLphoton[nE] = {360*nm,370*nm,380*nm,390*nm,400*nm,410*nm,420*nm,430*nm,440*nm,450*nm,460*nm,470*nm,480*nm,490*nm,500*nm,510*nm,520*nm,530*nm,540*nm,550*nm};
        G4double Ephoton[nE];
        G4double Reflectivity[nE];
        G4double Reflectivity_backwards[nE]  = { 0.0785,0.0817,0.1031,0.3326,0.6287,0.8252,0.8905,0.9147,0.9343,0.952,0.9632,0.965,0.9618,0.9573,0.9556,0.9545,0.9526,0.9571,0.9663,0.9733};
        for(int i=0; i<nE; i++){ 
            Ephoton[i]= wl2E(WLphoton[nE-1-i]);
            Reflectivity[i]=Reflectivity_backwards[nE-1-i];
        }
        G4double Efficiency[nE]    = { 0 };
        G4double SpecularLobe[nE]; init_array_flat(SpecularLobe,0.10,nE);
        G4double SpecularSpike[nE]; init_array_flat(SpecularSpike,0.90,nE);
        G4double Backscatter[nE]   = { 0 };

        G4MaterialPropertiesTable* mst = new G4MaterialPropertiesTable();
        mst->AddProperty("REFLECTIVITY", Ephoton, Reflectivity, nE);
        mst->AddProperty("EFFICIENCY", Ephoton, Efficiency, nE);
        mst->AddProperty("SPECULARLOBECONSTANT", Ephoton, SpecularLobe, nE);
        mst->AddProperty("SPECULARSPIKECONSTANT", Ephoton, SpecularSpike, nE);
        mst->AddProperty("BACKSCATTERCONSTANT", Ephoton, Backscatter, nE);
        
        surf->SetMaterialPropertiesTable(mst);
        surf->SetType(dielectric_metal);
        surf->SetModel(unified);
        surf->SetFinish(polished);
    }
    
    ESR=new G4OpticalSurface("ESR_surf",unified,groundfrontpainted,dielectric_metal);
    {//anonymous scope
        G4OpticalSurface* surf = ESR;
        const G4int nE = 20;                         // Edit: number of photon energies to specify

        G4double WLphoton[nE] = {360*nm,370*nm,380*nm,390*nm,400*nm,410*nm,420*nm,430*nm,440*nm,450*nm,460*nm,470*nm,480*nm,490*nm,500*nm,510*nm,520*nm,530*nm,540*nm,550*nm};//interpret as nm
        G4double Ephoton[nE];
        G4double Reflectivity[nE];
        G4double Reflectivity_backwards[nE]  = { 0.0840,0.1538,0.6569,0.8921,0.9422,0.9561,0.9624,0.9681,0.9719,0.9734,0.9750,0.9751,0.9750,0.9743,0.9732,0.9714,0.9707,0.9716,0.9727,0.9734};
//                G4double Reflectivity_backwards[nE]  = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
        for(int i=0; i<nE; i++){ 
            Ephoton[i]= wl2E(WLphoton[nE-1-i]);
            Reflectivity[i]=Reflectivity_backwards[nE-1-i];
        }
        G4double rindex[nE];
        init_array_flat(rindex, 1.492, nE);
        G4double Efficiency[nE]    = { 0 };
        G4double SpecularLobe[nE]; init_array_flat(SpecularLobe,0.01,nE);
        G4double SpecularSpike[nE]; init_array_flat(SpecularSpike,0.99,nE);
        G4double Backscatter[nE]   = { 0 };

        G4MaterialPropertiesTable* mst = new G4MaterialPropertiesTable();
        mst->AddProperty("RINDEX", Ephoton, rindex, nE);
        mst->AddProperty("REFLECTIVITY", Ephoton, Reflectivity, nE);
        mst->AddProperty("EFFICIENCY", Ephoton, Efficiency, nE);
        mst->AddProperty("SPECULARLOBECONSTANT", Ephoton, SpecularLobe, nE);
        mst->AddProperty("SPECULARSPIKECONSTANT", Ephoton, SpecularSpike, nE);
        mst->AddProperty("BACKSCATTERCONSTANT", Ephoton, Backscatter, nE);
        
        surf->SetMaterialPropertiesTable(mst);
//        surf->SetType(dielectric_metal);
//        surf->SetModel(unified);       
//        surf->SetFinish(ground);
        surf->SetSigmaAlpha(M_PI/2.);
    }
    ESR_warped=new G4OpticalSurface("ESR_warped_surf");
    {//anonymous scope
        G4OpticalSurface* surf = ESR_warped;
        const G4int nE = 20;                         // Edit: number of photon energies to specify

        G4double WLphoton[nE] = {360*nm,370*nm,380*nm,390*nm,400*nm,410*nm,420*nm,430*nm,440*nm,450*nm,460*nm,470*nm,480*nm,490*nm,500*nm,510*nm,520*nm,530*nm,540*nm,550*nm};//interpret as nm
        G4double Ephoton[nE];
        G4double Reflectivity[nE];
        G4double Reflectivity_backwards[nE]  = { 0.0840,0.1538,0.6569,0.8921,0.9422,0.9561,0.9624,0.9681,0.9719,0.9734,0.9750,0.9751,0.9750,0.9743,0.9732,0.9714,0.9707,0.9716,0.9727,0.9734};
//                G4double Reflectivity_backwards[nE]  = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
        for(int i=0; i<nE; i++){ 
            Ephoton[i]= wl2E(WLphoton[nE-1-i]);
            Reflectivity[i]=Reflectivity_backwards[nE-1-i];
        }
        G4double Efficiency[nE]    = { 0 };
        G4double SpecularLobe[nE]; init_array_flat(SpecularLobe,1.0,nE);
        G4double SpecularSpike[nE]; init_array_flat(SpecularSpike,0.0,nE);
        G4double Backscatter[nE]   = { 0 };

        G4MaterialPropertiesTable* mst = new G4MaterialPropertiesTable();
        mst->AddProperty("REFLECTIVITY", Ephoton, Reflectivity, nE);
        mst->AddProperty("EFFICIENCY", Ephoton, Efficiency, nE);
        mst->AddProperty("SPECULARLOBECONSTANT", Ephoton, SpecularLobe, nE);
        mst->AddProperty("SPECULARSPIKECONSTANT", Ephoton, SpecularSpike, nE);
        mst->AddProperty("BACKSCATTERCONSTANT", Ephoton, Backscatter, nE);
        
        surf->SetMaterialPropertiesTable(mst);
        surf->SetType(dielectric_metal);
        surf->SetModel(unified);       
        surf->SetFinish(ground);
        surf->SetSigmaAlpha(.2);
    }
//    FEP5mil = new G4OpticalSurface("FEP5mil",unified,ground,dielectric_dielectric);

    LUTtest = new G4OpticalSurface("LUTtest");{
        G4OpticalSurface* surf = LUTtest;

        surf->SetType(dielectric_LUT);
        surf->SetModel(LUT);
        surf->SetFinish(polishedvm2000air);
    }

    FEP5mil = new G4OpticalSurface("FEP5mil",unified,groundbackpainted,dielectric_dielectric);    
    {//anonymous scope
        G4OpticalSurface* surf = FEP5mil;
        const G4int nE = 20;                         // Edit: number of photon energies to specify
        G4double WLphoton[nE] = {360*nm,370*nm,380*nm,390*nm,400*nm,410*nm,420*nm,430*nm,440*nm,450*nm,460*nm,470*nm,480*nm,490*nm,500*nm,510*nm,520*nm,530*nm,540*nm,550*nm};//interpret as nm
        G4double Ephoton[nE];
        for(int i=0; i<nE; i++){ 
            Ephoton[i]= wl2E(WLphoton[nE-1-i]);
//            Reflectivity[i]=Reflectivity_backwards[nE-1-i];
//            Transmittance[i]=1-Reflectivity[i];
        }
        G4double Efficiency[nE]    = { 0 };
        G4double SpecularLobe[nE];
//        init_array_flat(SpecularLobe, 0.08, nE);
        init_array_flat(SpecularLobe, 1.0, nE);        
        G4double SpecularSpike[nE];
//        init_array_flat(SpecularSpike, 0.92, nE);
        init_array_flat(SpecularSpike, 0.0, nE);        
//        G4double Backscatter[nE]   = { 0 };
                G4double Reflectivity[nE];//AD
        init_array_flat(Reflectivity, 1.0, nE);//AD

        G4MaterialPropertiesTable* mst = new G4MaterialPropertiesTable();
        
//        mst->AddProperty("TRANSMITTANCE", Ephoton, Transmittance, nE);
        mst->AddProperty("EFFICIENCY", Ephoton, Efficiency, nE);
        mst->AddProperty("SPECULARLOBECONSTANT", Ephoton, SpecularLobe, nE);
        mst->AddProperty("SPECULARSPIKECONSTANT", Ephoton, SpecularSpike, nE);
        mst->AddProperty("REFLECTIVITY", Ephoton, Reflectivity, nE);
//        mst->AddProperty("BACKSCATTERCONSTANT", Ephoton, Backscatter, nE);
        
        surf->SetMaterialPropertiesTable(mst);
        surf->SetSigmaAlpha(4.0*deg);
    }
    
    Black=GenericSpecular(0);
    
}

G4OpticalSurface* SurfacesHelper::GenericSpecular(G4double reflectivity){
    G4OpticalSurface* surf = new G4OpticalSurface("GenericSpecular"+to_str(reflectivity));
    const G4int nE = 2;                         // Edit: number of photon energies to specify

    G4double Ephoton[nE] = {1.5*eV, 6*eV};
    G4double Reflectivity[nE]; init_array_flat(Reflectivity,reflectivity,nE);
    G4double Efficiency[nE]    = { 0 };
    G4double SpecularLobe[nE]; init_array_flat(SpecularLobe,0.0,nE);
    G4double SpecularSpike[nE]; init_array_flat(SpecularSpike,1.0,nE);
    G4double Backscatter[nE]   = { 0 };

    G4MaterialPropertiesTable* mst = new G4MaterialPropertiesTable();
    mst->AddProperty("REFLECTIVITY", Ephoton, Reflectivity, nE);
    mst->AddProperty("EFFICIENCY", Ephoton, Efficiency, nE);
    mst->AddProperty("SPECULARLOBECONSTANT", Ephoton, SpecularLobe, nE);
    mst->AddProperty("SPECULARSPIKECONSTANT", Ephoton, SpecularSpike, nE);
    mst->AddProperty("BACKSCATTERCONSTANT", Ephoton, Backscatter, nE);

    surf->SetMaterialPropertiesTable(mst);
    surf->SetType(dielectric_metal);
    surf->SetModel(unified);
    surf->SetFinish(polished);

    return surf;
}
