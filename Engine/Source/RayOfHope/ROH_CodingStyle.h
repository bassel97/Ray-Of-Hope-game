// // Copyright di-tri.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ROH_CodingStyle.generated.h"

/**
 * Every file in our code should start with ROH_
 * Give an explanation of what should this class be responsible of.
 */
UCLASS()
class RAYOFHOPE_API UROH_CodingStyle : public UObject
{
	GENERATED_BODY()

	// Order: public methods, public variables, protected methods,
	//        protected variables, private methods, private variables.
public:
	void DoFunction();
	int32 CalculateValue();

	// Write the definition of function in header if it is one line
	// This is the naming of the boolean returning function.
	bool IsBoolean() const { return bIsBoolean; }

public:
	// Add initial value for variables.
	int32 SomeData = 0;


private:
	// This is the definition of a boolean variable.
	bool bIsBoolean = false;

};
