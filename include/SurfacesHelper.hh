/// \file SurfacesHelper.hh Materials definitions used in detector geometries.
#ifndef SURFACESSHELPER_HH
/// Assure this header is loaded only once
#define SURFACESSHELPER_HH

#include <map>
#include <string>

#include <G4OpticalSurface.hh>

using std::string;
using std::map;

/// Class with singleton instance providing materials properties
class SurfacesHelper {
public:
    /// get instance reference
    static SurfacesHelper& S();
    
    G4OpticalSurface* SolarMirror;    
    G4OpticalSurface* ESR; //aka 3M foil
    G4OpticalSurface* ESR_warped; //aka 3M foi
    G4OpticalSurface* Black;
    G4OpticalSurface* FEP5mil;
    
    G4OpticalSurface* GenericSpecular(G4double reflectivity);
    
protected:
    /// Constructor
    SurfacesHelper();
    /// set up material optical properties
        
    static SurfacesHelper* theSurfHelper;       ///< singleton instance
    
};


#endif
