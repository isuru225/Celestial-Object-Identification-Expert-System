
CLIPS> (defrule Menu
(not(viewingMethod ?))
=>
(printout t  crlf crlf
"The celestial object is viewed by " crlf crlf
"(1):By naked-eye" crlf crlf
"(2):By special instruments" crlf crlf
"Enter your response (1|2) :")
(assert (viewingMethod (read))))

:; Rule Celestial object has an appearance like
:; Rule 0
CLIPS> (defrule Naked_Eye
(viewingMethod 1)
(not(objectAppearance ?))
=>
(printout t crlf 
"Celestial object has an appearance like..." crlf
"(1):A point light" crlf
"(2):A extended light" crlf
"Enter your response (1|2): ")
(assert (objectAppearance (read))))

:; Rule 1
CLIPS>  (defrule PointLight
(viewingMethod 1)
(objectAppearance 1)
?retractResApp <- (objectAppearance 1)
?retractResView <- (viewingMethod 1)
(not(isTwinkling ?))
=>
(retract ?retractResApp)
(retract ?retractResView)
(printout t crlf 
"Is point light is twinkling" crlf
"(1):Yes" crlf
"(2):No" crlf
"Enter your response (1|2): ")
(assert (isTwinkling (read))))

:; Rule 2
CLIPS>  (defrule ExtendedLight
(viewingMethod 1)
(objectAppearance 2)
?retractResApp <- (objectAppearance 2)
?retractResView <- (viewingMethod 1)
(not(isLocatedInPolarRegion ?))
=>
(retract ?retractResApp)
(retract ?retractResView)
(printout t crlf 
"Is extended light is appearing in polar regions..." crlf
"(1):Yes" crlf
"(2):No" crlf
"Enter your response (1|2): ")
(assert (isLocatedInPolarRegion (read))))

:; rule 3 (===> Twinking)
CLIPS> (defrule Twinkling
(isTwinkling 1)
?retractResTwin <- (isTwinkling 1)
(not(hasMotion ?))
=>
(retract ?retractResTwin)
(printout t crlf 
"Object has a motion..." crlf
"(1):Relative to other stars" crlf
"(2):Relative to earth" crlf
"Enter your response (1|2): ")
(assert (hasMotion (read))))

:; rule 4 (===> NotTwinking)
CLIPS> (defrule NotTwinkling
(isTwinkling 2)
?retractResTwin <- (isTwinkling 2)
(not(hasMotion ?))
=>
:;(retract ?retractResTwin)
(printout t crlf 
"Object has a motion..." crlf
"(1):Orbital motion" crlf
"(2):Non orbital" crlf
"Enter your response (1|2): ")
(assert (hasMotion (read))))

:; rule 5 (===> RelativeToOtherStars)
CLIPS> (defrule RelativeToOtherStars
(not(isTwinkling 2))
(hasMotion 1)
?retractResMos <- (hasMotion 1)
=>
(retract ?retractResMos)
(printout t crlf
"<==== Final Output ====>" crlf 
"The celestial objecct is a proper motion star!"))

:; rule 6 (===> RelativeToEarth)
CLIPS> (defrule RelativeToEarth
(not(isTwinkling 2))
(hasMotion 2)
?retractResMos <- (hasMotion 2)
(not(visibleLightColorOfObject ?))
=>
(retract ?retractResMos)
(printout t crlf
"Visible light color of object is..." crlf 
"(1): Red" crlf
"(2): Blue" crlf
"Enter your response (1|2): ")
(assert (visibleLightColorOfObject (read))))

:; rule 7 (===> lightColorRed)
CLIPS> (defrule lightColorRed
(visibleLightColorOfObject 1)
?retractResColor <- (visibleLightColorOfObject 1)
=>
(retract ?retractResColor)
(printout t crlf
"<==== Final Output ====>" crlf 
"The celestial objecct is a negative radio star!"))

:; rule 8 (===> lightColorBlue)
CLIPS> (defrule lightColorBlue
(visibleLightColorOfObject 2)
?retractResColor <- (visibleLightColorOfObject 2)
=>
(retract ?retractResColor)
(printout t crlf
"<==== Final Output ====>" crlf 
"The celestial objecct is a positive radio star!"))

:; rule 9 (===> orbitalMotion)
CLIPS> (defrule orbitalMotion
(isTwinkling 2)
(hasMotion 1)
?retractResMos <- (hasMotion 1)
?retractResTwin <- (isTwinkling 2)
(not(orbitIsAround ?))
=>
(retract ?retractResMos)
(retract ?retractResTwin)
(printout t crlf
"Orbit of celestail object is around..." crlf 
"(1):A star" crlf
"(2):A planet" crlf
"Enter your response (1|2): ")
(assert (orbitIsAround (read))))

:; rule 10 (===> centralizedStarObject)
CLIPS> (defrule centralizedStarObject
(orbitIsAround 1)
?retractResCenter <- (orbitIsAround 1)
=>
(retract ?retractResCenter)
(printout t crlf
"<==== Final Output ====>" crlf
"The celestial objecct is a planet!"))

:; rule 11 (===> centralizedPlanetObject)
CLIPS> (defrule centralizedPlanetObject
(orbitIsAround 2)
?retractResCenter <- (orbitIsAround 2)
=>
(retract ?retractResCenter)
(printout t crlf
"<==== Final Output ====>" crlf
"The celestial objecct is a moon!"))

:; rule 12 (===> NonOrbitalMotion)
CLIPS> (defrule nonOrbitalMotion
(isTwinkling 2)
(hasMotion 2)
?retractResMos <- (hasMotion 2)
?retractResTwin <- (isTwinkling 2)
(not(orbitIsAround ?))
=>
(retract ?retractResMos)
(retract ?retractResTwin)
(printout t crlf
"<==== Final Output ====>" crlf 
"The celestial objecct is an UFO or Unknown object!"))

:; rule 13 (===> polarRegion)
CLIPS> (defrule polarRegion
(isLocatedInPolarRegion 1)
?retractResPolar <- (isLocatedInPolarRegion 1)
=>
(retract ?retractResPolar)
(printout t crlf
"<==== Final Output ====>" crlf 
"The celestial objecct is an aurora!"))

:; rule 14 (===> NotpolarRegion)
CLIPS> (defrule notPolarRegion
(isLocatedInPolarRegion 2)
?retractResPolar <- (isLocatedInPolarRegion 2)
=>
(retract ?retractResPolar)
(printout t crlf
"<==== Final Output ====>" crlf 
"The celestial objecct is a galaxy or a nebulae!"))

/////////////////////////
//considering the right branch

:; rule 15 (===> specialInstruments)
CLIPS> (defrule specialInstruments
(viewingMethod 2)
?retractRes1 <- (viewingMethod 2)
(not(objectAppearance ?))
=>
(printout t crlf
"Celestial object has an appearance like..." crlf
"(1):A spiral" crlf
"(2):An elliptical" crlf
"(3):A lenticular" crlf
"(4):A fuzzy tail and head with distinct nucleus" crlf
"(5):A faint point of light and irregular shape" crlf
"(6):A diffusive and cloudy" crlf
"(7):A sphere shape" crlf
"Enter your response (1|2|3|4|5|6|7): ")
(assert (objectAppearance (read))))

:; rule 16 (===> spiralEllipticalLenticular)
CLIPS> (defrule spiralEllipticalLenticular
(or (objectAppearance 1) (objectAppearance 2) (objectAppearance 3))
(viewingMethod 2)
?retractResApp <- (objectAppearance ?option)
?retractResView <- (viewingMethod 2)
(not(luminosityLvl ?))
=>
(retract ?retractResApp)
(retract ?retractResView)
(printout t crlf
"What is the luminosity level as percentage..." crlf
"Enter your response (Eg-40): ")
(assert (luminosityLvl (read))))


:; rule 17 (===> luminosityLevel)
(defrule luminosityLevel
   (luminosityLvl ?luminosityLvl)
   ?retractResLum <- (luminosityLvl ?luminosityLvl)
   =>
   (if (<= ?luminosityLvl 100)
      then
      (if (>= ?luminosityLvl 70)
         then
         (retract ?retractResLum)
         (printout t 
         "<==== Final Output ====>" crlf
         "The celestial objecct is a quasar luminosity galaxy!" crlf)
      )
      (if (and (< ?luminosityLvl 70) (>= ?luminosityLvl 40))
         then
         (retract ?retractResLum)
         (printout t 
         "<==== Final Output ====>" crlf
         "The celestial objecct is an sub luminous galaxy!" crlf)
      )
       (if (and (< ?luminosityLvl 40) (>= ?luminosityLvl 0))
         then
         (retract ?retractResLum)
         (printout t 
         "<==== Final Output ====>" crlf
         "The celestial objecct is a low luminosity galaxy!" crlf)
      )
   else
      (retract ?retractResLum)
      (printout t "Invalid luminosity level" crlf)
   )
)

rule 18 (===> fuzzyTailNucleus)
CLIPS> (defrule fuzzyTailNucleus
(objectAppearance 4)
(viewingMethod 2)
?retractResApp <- (objectAppearance 4)
?retractResView <- (viewingMethod 2)
(not(orbitNature ?))
=>
(retract ?retractResApp)
(retract ?retractResView)
(printout t crlf
"Has an orbit which is..." crlf
"(1): near to the sun" crlf
"(2): near to the jupiter" crlf
"(3): disrupted or destroyed" crlf
"Enter your response(1|2|3): ")
(assert (orbitNature (read))))

:; rule 19 (===> OrbitNature)
(defrule OrbitNature
   (orbitNature ?orbitNature)
   ?retractResOrbit <- (orbitNature ?orbitNature)
   =>
   (if (<= ?orbitNature 3)
      then
      (if (= ?orbitNature 1)
         then
         (retract ?retractResOrbit)
         (printout t 
         "<==== Final Output ====>" crlf
         "The celestial objecct is a sungrazer comet!" crlf)
      )
      (if  (= ?orbitNature 2)
         then
         (retract ?retractResOrbit)
         (printout t 
         "<==== Final Output ====>" crlf
         "The celestial objecct is a jupiter-family comet!" crlf)
      )
       (if (= ?orbitNature 3)
         then
         (retract ?retractResOrbit)
         (printout t 
         "<==== Final Output ====>" crlf
         "The celestial objecct is an extinct comet!" crlf)
      )
   else
      (retract ?retractResOrbit)
      (printout t "Invalid answer" crlf)
   )
)

rule 20 (===> asteroidColorFinder)
(defrule asteroidColorFinder
(objectAppearance 5)
(viewingMethod 2)
?retractResApp <- (objectAppearance 5)
?retractResView <- (viewingMethod 2)
(not(asteroidColor ?))
=>
(retract ?retractResApp)
(retract ?retractResView)
(printout t crlf
"Visible color of comet is..." crlf
"(1): dark reddish" crlf
"(2): bright reddish" crlf
"(3): metalic" crlf
"Enter your response(1|2|3): ")
(assert (asteroidColor (read))))

:; rule 21 (===> asteroidTypeFinder)
(defrule asteroidTypeFinder
   (asteroidColor ?asteroidColor)
   ?retractResAsteroidColor <- (asteroidColor ?asteroidColor)
   =>
   (if (<= ?asteroidColor 3)
      then
      (if (= ?asteroidColor 1)
         then
         (retract ?retractResAsteroidColor)
         (printout t 
         "<==== Final Output ====>" crlf
         "The celestial objecct is a type C asteroid!" crlf)
      )
      (if  (= ?asteroidColor 2)
         then
         (retract ?retractResAsteroidColor)
         (printout t 
         "<==== Final Output ====>" crlf
         "The celestial objecct is a type S asteroid!" crlf)
      )
       (if (= ?asteroidColor 3)
         then
         (retract ?retractResAsteroidColor)
         (printout t 
         "<==== Final Output ====>" crlf
         "The celestial objecct is a type M asteroid!" crlf)
      )
   else
      (retract ?retractResAsteroidColor)
      (printout t "Invalid answer" crlf)
   )
)

:; rule 22 (===> nebulaeCompositionFinder)
CLIPS> (defrule nebulaeCompositionFinder
(objectAppearance 6)
(viewingMethod 2)
?retractResApp <- (objectAppearance 6)
?retractResView <- (viewingMethod 2)
(not(nebulaeComposition ?))
=>
(retract ?retractResApp)
(retract ?retractResView)
(printout t crlf
"The celestial object is composed by..." crlf
"(1): gas and dust" crlf
"(2): remnants of stars" crlf
"Enter your response(1|2): ")
(assert (nebulaeComposition (read))))


//***********************************************
 :;?retractResNebComp <- (nebulaeComposition 2)
 :;?retractResNebComp <- (nebulaeComposition 1)
//**********************************************

:; rule 23 (===> nebulaeColorSet1Finder)
(defrule asteroidColorSet1Finder
  (nebulaeComposition 1)
  (not(nebColor ?))
  =>
  (printout t crlf
    "Visible color of the object is..." crlf
    "(1): Red" crlf
    "(2): Black" crlf
    "(3): Other" crlf
    "Enter your response(1|2|3): ")
    (assert (nebColor (read)))
)

:; rule 24 (===> nebulaeColorSet2Finder)
(defrule asteroidColorSet2Finder
  (nebulaeComposition 2)
  (not(nebColor ?))
  =>
  (printout t crlf
    "Visible color of the object is..." crlf
    "(1): Green" crlf
    "(2): black" crlf
    "Enter your response(1|2): ")
    (assert (nebColor (read)))
)

:; rule 25 (===> nebulaeTypeFinder)
(defrule nebulaeTypeFinder
   (nebulaeComposition ?nebulaeComposition)
   (nebColor ?nebColor)
   ?retractResNebColor <- (nebColor ?nebColor)
   ?retractResNebComp <- (nebulaeComposition ?nebulaeComposition)
   =>
   (if (= ?nebulaeComposition 1)
      then
      (if (= ?nebColor 1)
         then
         (retract ?retractResNebColor)
         (retract ?retractResNebComp)
         (printout t 
         "<==== Final Output ====>" crlf
         "The celestial objecct is an emission nebulae!" crlf)
      )
      (if  (= ?nebColor 2)
         then
         (retract ?retractResNebColor)
         (retract ?retractResNebComp)
         (printout t 
         "<==== Final Output ====>" crlf
         "The celestial objecct is a dark nebulae!" crlf)
      )
       (if (= ?nebColor 3)
         then
         (retract ?retractResNebColor)
         (retract ?retractResNebComp)
         (printout t 
         "<==== Final Output ====>" crlf
         "The celestial objecct is a reflection nebulae!" crlf)
      )
   else
      (retract ?retractResNebColor)
      (retract ?retractResNebComp)
   )

    (if (= ?nebulaeComposition 2)
      then
      (if (= ?nebColor 1)
         then
         (retract ?retractResNebColor)
         (retract ?retractResNebComp)
         (printout t 
         "<==== Final Output ====>" crlf
         "The celestial objecct is a planetary nebulae!" crlf)
      )
      (if  (= ?nebColor 2)
         then
         (retract ?retractResNebColor)
         (retract ?retractResNebComp)
         (printout t 
         "<==== Final Output ====>" crlf
         "The celestial objecct is an emission nebulae!" crlf)
      )
   else
      (retract ?retractResNebColor)
      (retract ?retractResNebComp)
   )

)



:;rule 26 (===> gravitationalPowerDetector)
(defrule gravitationalPowerDetector
(objectAppearance 7)
(viewingMethod 2)
?retractResApp <- (objectAppearance 7)
?retractResView <- (viewingMethod 2)
(not(natureOfGravity ?))
=>
(retract ?retractResApp)
(retract ?retractResView)
(printout t crlf
"Object has a " crlf
"(1): Abnormal massive gravitational power" crlf
"(2): Normal gravitational power" crlf
"Enter your response(1|2): ")
(assert (natureOfGravity (read))))

:;rule 27 (===> solarMassesFinder)
(defrule solarMassesFinder
(natureOfGravity 1)
?retractResGrav <- (natureOfGravity 1)
(not(noOfSolarMasses ?))
=>
(retract ?retractResGrav)
(printout t crlf
"How many number of solar masses involve to create..." crlf
"(1): 1-100" crlf
"(2): 100-100000" crlf
"(3): 100000-10^9" crlf
"Enter your response(1|2|3): ")
(assert (noOfSolarMasses (read))))

:;rule 28 (===> natureOFLightEmission)
(defrule natureOFLightEmission
(natureOfGravity 2)
?retractResGrav <- (natureOfGravity 2)
(not(isLightsource ?))
=>
(retract ?retractResGrav)
(printout t crlf
"Is object a light source..." crlf
"(1): Yes" crlf
"(2): No" crlf crlf
"Enter your response(1|2): ")
(assert (isLightsource (read))))


:;rule 29 (===> blackHoleTypeFinder)
(defrule blackHoleTypeFinder
   (noOfSolarMasses ?noOfSolarMasses)
   ?retractResSolarMasses <- (noOfSolarMasses ?noOfSolarMasses)
   =>
   (if (<= ?noOfSolarMasses 3)
      then
      (if (= ?noOfSolarMasses 1)
         then
         (retract ?retractResSolarMasses)
         (printout t 
         "<==== Final Output ====>" crlf
         "The celestial objecct is a stellar black hole!" crlf)
      )
      (if  (= ?noOfSolarMasses 2)
         then
         (retract ?retractResSolarMasses)
         (printout t 
         "<==== Final Output ====>" crlf
         "The celestial objecct is an intermidiate mass black hole!" crlf)
      )
       (if (= ?noOfSolarMasses 3)
         then
         (retract ?retractResSolarMasses)
         (printout t 
         "<==== Final Output ====>" crlf
         "The celestial objecct is a super massive black hole!" crlf)
      )
   else
      (retract ?retractResSolarMasses)
      (printout t "Invalid answer" crlf)
   )
)

:;rule 30 (===> objectFinder)
(defrule objectFinder
   (isLightsource ?isLightsource)
   ?retractResLight <- (isLightsource ?isLightsource)
   =>
   (if (<= ?isLightsource 2)
      then
      (if (= ?isLightsource 1)
         then
         (retract ?retractResLight)
         (printout t 
         "<==== Final Output ====>" crlf
         "The celestial objecct is a star!" crlf)
      )
      (if  (= ?isLightsource 2)
         then
         (retract ?retractResLight)
         (printout t 
         "<==== Final Output ====>" crlf
         "The celestial objecct is a planet!" crlf)
      )
   else
      (retract ?retractResLight)
      (printout t "Invalid answer" crlf)
   )
)

