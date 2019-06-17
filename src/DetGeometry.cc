//#define Tube_With_Mixture
#define Poly


#include "DetGeometry.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4Color.hh"
#include "G4RotationMatrix.hh"
#include "G4Sphere.hh"
#include "G4SubtractionSolid.hh"

DetGeometry::DetGeometry() {

}

DetGeometry::~DetGeometry() {}

G4VPhysicalVolume* DetGeometry::Construct(){

    G4NistManager* nist = G4NistManager::Instance();

    G4double size = 1*m;

    G4Material* world_mat = nist->FindOrBuildMaterial("G4_Galactic");

    G4Box* solidWorld =
      new G4Box("World",
         0.5*size, 0.5*size, 0.5*size);

    G4LogicalVolume* logicWorld =
      new G4LogicalVolume(solidWorld,
                          world_mat,
                          "World");

logicWorld->SetVisAttributes(G4VisAttributes::Invisible);

 G4VPhysicalVolume* physWorld =
      new G4PVPlacement(0,
                        G4ThreeVector(),
                        logicWorld,
                        "World",
                        0,
                        false,
                        0);





// Define meterials (Boric Acid, Water, Helium, Am-Be, etc.)

    G4String name,symbol;
    G4double abundance, aH, aO, z, ncomponents,
    H3BO3_density, H3BO3_mass,
    H2O_density, H2O_volume,
    mix_volume, mix_density,
    Am_density, Be_density, AmBe_density,
    AmBe_temp, AmBe_press,
    temperature, pressure, fractionmass;
    G4int nIsotopes,natoms;
    G4double He3_temp, He3_press, He3_density;

    Am_density = 13.67*g/cm3;
    Be_density = 1.848*g/cm3;
    AmBe_density = 4.2124;
    AmBe_press = 1*atmosphere;
    AmBe_temp = 300*kelvin;

    He3_temp = 300*kelvin;
    He3_press = 4*atmosphere;
    He3_density = 0.0005*g/cm3;
    temperature = 300.*kelvin;
    pressure = 1.*atmosphere;
    H2O_density = 1*g/cm3;
    mix_volume = 1000*cm3;
    H3BO3_mass = 55*g;
    H3BO3_density = 1.435*g/cm3;
    H2O_volume = mix_volume-H3BO3_mass/H3BO3_density;
    mix_density = (H3BO3_mass+H2O_density*H2O_volume)/mix_volume;
//    G4cout << "mix density  is " << mix_density/(g/cm3) << G4endl;

    //Define common elements
    aH = 1.00784*g/mole;
    G4Element*elH = new G4Element(name="Hydrogen", symbol="H", z = 1., aH);

    aO = 15.999*g/mole;
    G4Element*elO = new G4Element(name="Oxygen", symbol="O", z = 8., aO);

    //Define isotopes of B
    G4Isotope*B10 = new G4Isotope(name="B10", 5, 10, 10.012*g/mole);
    G4Isotope*B11 = new G4Isotope(name="B11", 5, 11, 11.009*g/mole);


    //Define element  Boron from isotopes
    G4Element* elBoron = new G4Element(name="Boron", symbol="B", nIsotopes=2);
    elBoron->AddIsotope(B10,abundance= 18.5*perCent);
    elBoron->AddIsotope(B11,abundance= 81.5*perCent);

    //Define Boric Acid

    G4Material*H3BO3 = new G4Material(name="Boron_Acid", H3BO3_density, ncomponents = 3, kStateSolid, temperature, pressure);
    H3BO3->AddElement(elBoron, natoms = 1);
    H3BO3->AddElement(elH, natoms = 3);
    H3BO3->AddElement(elO, natoms = 3);

    //Define H2O (liquid Water)

    G4Material*H2O = new G4Material(name="Water", H2O_density, ncomponents = 2, kStateLiquid, temperature, pressure);
    H2O->AddElement(elH, natoms = 2);
    H2O->AddElement(elO, natoms = 1);

    //Define Boric Acid mix with Water (material)

    G4Material*Mix_mat = new G4Material(name="Mixture", mix_density, ncomponents = 2, kStateLiquid, temperature, pressure);

    Mix_mat->AddMaterial(H3BO3,fractionmass = (100*(H3BO3_mass/H3BO3_density)/(mix_volume)*perCent));
//    G4cout << "fractionmass of boric acid is " << fractionmass << G4endl;

    Mix_mat->AddMaterial(H2O,fractionmass = (100*(H2O_volume)/(mix_volume))*perCent);
//    G4cout << "fractionmass of H2O  is " << fractionmass << G4endl;


    //Define Helium isotope
    G4Isotope*He3 = new G4Isotope(name="He3", 2, 3, 3.016*g/mole);
    //Define element from Helium isotope
    G4Element* elHe3 = new G4Element(name="He3", symbol="He", nIsotopes=1);
    elHe3->AddIsotope(He3,abundance= 100*perCent);
    //Define Helium material
    G4Material*He3_mat = new G4Material(name="Helium3", He3_density, ncomponents = 1, kStateGas, He3_temp, He3_press);
    He3_mat->AddElement(elHe3, natoms = 1);

    //Define Void material
    G4Material*Void_mat = nist->FindOrBuildMaterial("G4_Galactic");

    //Define material of Helium counter housing
    G4Material*Counter_mat = nist->FindOrBuildMaterial("G4_Al");

    //Define material of mixture housing
    G4Material*Tube_mat = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");

    //Define material of Cadmium sheild
    G4Material*Cd_mat = nist->FindOrBuildMaterial("G4_Cd");

    //Define material of Polyethylene
    G4Material*Poly_mat = nist->FindOrBuildMaterial("G4_POLYETHYLENE");

    //  Create rotation matrix of the objects
    G4RotationMatrix* myRotation = new G4RotationMatrix();
    myRotation->rotateX(0.*deg);
    myRotation->rotateY(90.*deg);
    myRotation->rotateZ(0.*rad);


    // define distances

    G4double Rtube, dtube, Htube, Rcnt, dcnt, Hcnt, dshld,
    Zsrc, Xsrc, Ysrc,
    Ztube, Xtube, Ytube,
    Zcnt1, Xcnt1, Ycnt1;

    Rtube=6;
    dtube=0.4;
    Htube=15;
    Rcnt=1.5;
    dcnt=0.1;
    Hcnt=11;
    dshld=19;

    Xsrc=0, Ysrc=0, Zsrc=(Rtube+6);
    Xtube=0, Ytube=0, Ztube=0;
    Xcnt1=0, Ycnt1=0, Zcnt1=-(Rtube+2);




#ifdef Tube_With_Mixture

    //Define Boric Acid mix with Water (place in space)

    G4ThreeVector Mix_pos = G4ThreeVector(Xtube*cm, Ytube*cm, Ztube*cm);

    G4Tubs*Mix = new G4Tubs("Mixture", 0*cm, (Rtube-dtube)*cm, Htube*cm, 0*deg, 360*deg);

    G4LogicalVolume*logicMix = new G4LogicalVolume(Mix, Mix_mat, "Mixture");

    G4VisAttributes*logicVisMix = new G4VisAttributes(G4Colour(5, 0.5, 0.5));

    logicMix->SetVisAttributes(logicVisMix);

    new G4PVPlacement(myRotation,
                      Mix_pos,
                      logicMix,
                      "Mixture",
                      logicWorld,
                      false,
                      0);

    // create an Tube part (Mixture housing)

    G4ThreeVector Tube_pos = G4ThreeVector(Xtube*cm, Ytube*cm, Ztube*cm);

    G4Tubs*Tube = new G4Tubs("MixTube", (Rtube-dtube)*cm, Rtube*cm, Htube*cm, 0*deg, 360*deg);

    G4LogicalVolume*logicTube = new G4LogicalVolume(Tube, Tube_mat, "MixTube");

    G4VisAttributes*logicVisTube = new G4VisAttributes(G4Colour(0.1, 0.1, 0.8));

    logicTube->SetVisAttributes(logicVisTube);

    new G4PVPlacement(myRotation,
                      Tube_pos,
                      logicTube,
                      "MixTube",
                      logicWorld,
                      false,
                      0);

#endif

    // create an He3 counter #1 housing

    G4ThreeVector Counter1_pos = G4ThreeVector(Xcnt1*cm, Ycnt1*cm, Zcnt1*cm);

    G4Tubs*Counter1_0 = new G4Tubs("Counter1_0", 0*cm, Rcnt*cm, Hcnt*cm, 0*deg, 360*deg);

    G4Tubs*Counter1_1 = new G4Tubs("Counter1_1", 0*cm, (Rcnt-dcnt)*cm, (Hcnt-dcnt)*cm, 0*deg, 360*deg);

    G4SubtractionSolid*Counter1 = new G4SubtractionSolid ("Counter1", Counter1_0, Counter1_1);

    G4LogicalVolume*logicCounter1 = new G4LogicalVolume(Counter1, Counter_mat, "Counter1");

    G4VisAttributes*logicVisCounter1 = new G4VisAttributes(G4Colour(0.7, 0.2, 0.1));

    logicCounter1->SetVisAttributes(logicVisCounter1);

    new G4PVPlacement(myRotation,
                      Counter1_pos,
                      logicCounter1,
                      "Counter1",
                      logicWorld,
                      false,
                      0);

    // filling helium counter #1 with He3 isotope

    G4ThreeVector He3_pos1 = G4ThreeVector(Xcnt1*cm, Ycnt1*cm, Zcnt1*cm);

    G4Tubs*He3_gas1 = new G4Tubs("He3_gas1", 0*cm, (Rcnt-dcnt)*cm, (Hcnt-dcnt)*cm, 0*deg, 360*deg);

    G4LogicalVolume*logicHe3_gas1 = new G4LogicalVolume(He3_gas1, He3_mat, "He3_gas1");

    G4VisAttributes*logicVisHe3_gas1 = new G4VisAttributes(G4Colour(0.1, 0.8, 0.1));

    logicHe3_gas1->SetVisAttributes(logicVisHe3_gas1);

    new G4PVPlacement(myRotation,
                      He3_pos1,
                      logicHe3_gas1,
                      "He3_gas1",
                      logicWorld,
                      true,
                      0);



    // create an Polyethylene shield for counter #1

#ifdef Poly

    G4ThreeVector Shield_pos = G4ThreeVector(Xcnt1*cm, Ycnt1*cm, Zcnt1*cm);

    G4Tubs*Shield0 = new G4Tubs("Shield0", 0*cm, (Rcnt+dshld)*cm, (Hcnt+dshld)*cm, 0*deg, 360*deg);

    G4Tubs*Shield1 = new G4Tubs("Shield1", 0*cm, Rcnt*cm, Hcnt*cm, 0*deg, 360*deg);

    G4SubtractionSolid*Shield = new G4SubtractionSolid ("Shield", Shield0, Shield1);

    G4LogicalVolume*logicShield = new G4LogicalVolume(Shield, Poly_mat, "Shield");

    G4VisAttributes*logicVisShield = new G4VisAttributes(G4Colour(149, 143, 121));

    logicShield->SetVisAttributes(logicVisShield);

    new G4PVPlacement(myRotation,
                      Shield_pos,
                      logicShield,
                      "Shield",
                      logicWorld,
                      false,
                      0);

#endif

    // create an SOURSE

//    G4ThreeVector Source_pos = G4ThreeVector(Xsrc*cm, Ysrc*cm, Zsrc*cm);
//
//    G4Tubs*Source = new G4Tubs("Source", 0*cm, 1.6*cm, 1.6*cm, 0*deg, 360*deg);
//
//    G4LogicalVolume*logicSource = new G4LogicalVolume(Source, Void_mat, "Source");
////    G4LogicalVolume*logicSource = new G4LogicalVolume(Source, nist->FindOrBuildMaterial("G4_Galactic"), "Source");
//
//    G4VisAttributes*logicVisSource = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0));
//
//    logicSource->SetVisAttributes(logicVisSource);
//
//
//    new G4PVPlacement(myRotation,
//                      Source_pos,
//                      logicSource,
//                      "Source",
//                      logicWorld,
//                      false,
//                      0);



    return physWorld;
}
