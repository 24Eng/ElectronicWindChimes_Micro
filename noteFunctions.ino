// Ensure that the note about to be played is within the limits.
int maintainNoteLimits(int funStartingPoint, int funRequestedChange, int funScaleType, int funScaleCount, int funLowerLimit, int funUpperLimit){
  int safelyRangedChange;
  boolean alteredOnce = true;
  int requestedNote = funStartingPoint + calculateScale(funRequestedChange, funScaleType, funScaleCount);
//  Serial.println();
//  Serial.print("Requested Change:\t");
//  Serial.print(funRequestedChange);
//  Serial.print("\tRequested Note:\t");
//  Serial.println(requestedNote);
//  Serial.println(calculateScale(funRequestedChange, funScaleType, funScaleCount));
  // Assess if the requested note needs to be raised to keep it above the lower threshold.
  if (requestedNote < funLowerLimit){
    // If the requested change is already greater than six, the limits were probably
    // changed recently so just keep going to a higher note. Else, add six make the change positive.
    if (funRequestedChange > 6){
      safelyRangedChange = funRequestedChange;
      alteredOnce = false;
    }else{
      safelyRangedChange = 6 + funRequestedChange;
      alteredOnce = false;
    }
  }
  // Assess if the requested note needs to be lowered to keep it below the upper threshold.
  if ((requestedNote > funUpperLimit) && alteredOnce){
    // If the requested change is already less than six, the limits were probably
    // changed recently so just keep going to a lower note. Else, subtract six to make the change negative.
    if (funRequestedChange < 6){
      safelyRangedChange = funRequestedChange;
    }else{
      safelyRangedChange = funRequestedChange - 6;
    }
  }
//  Serial.print("Somehow escaped\t ");
  return safelyRangedChange;
}

int calculateScale(int funDelta, int funScaleType, int funScaleTypes){
  // If an invalid scale type is sent, return 0, which will cause
  // the same note to be played repeatedly.
  if (funScaleType < 0 || funScaleType > funScaleTypes){
    return 0;
  }
  switch(funScaleType){
    case 0:
      return minorPentatonicScale[funDelta];
    case 1:
      return majorPentatonicScale[funDelta];
    case 2:
      return EgyptianPentatonicScale[funDelta];
    case 3:
      return bluesMinorPentatonicScale[funDelta];
    case 4:
      return bluesMajorPentatonicScale[funDelta];
    case 5:
      // This special mode will allow different things to be tested
      // on the same note for comparison's sake.
      return 0;
    return 0;
  }
}
