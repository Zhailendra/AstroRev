// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/MyLegacyCameraShake.h"

UMyLegacyCameraShake::UMyLegacyCameraShake()
{
	SetOscillationSettings();
}

void UMyLegacyCameraShake::SetOscillationSettings()
{
	OscillationDuration = 0.5f;
	OscillationBlendInTime = 0.5f;
	OscillationBlendOutTime = 0.5f;

	RotOscillation.Pitch.Amplitude = 1.1f;
	RotOscillation.Pitch.Frequency = 1.4f;

	RotOscillation.Yaw.Amplitude = 1.05f;
	RotOscillation.Yaw.Frequency = 1.f;

	RotOscillation.Roll.Amplitude = 1.25f;
	RotOscillation.Roll.Frequency = 1.f;

	LocOscillation.X.Amplitude = 3.75f;
	LocOscillation.X.Frequency = 3.5f;

	LocOscillation.Y.Amplitude = 3.5f;
	LocOscillation.Y.Frequency = 2.0f;

	LocOscillation.Z.Amplitude = 3.25f;
	LocOscillation.Z.Frequency = 3.0f;
}
