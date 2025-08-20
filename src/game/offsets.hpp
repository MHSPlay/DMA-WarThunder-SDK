#pragma once

namespace offsets
{
	constexpr uintptr_t cgame_offset = 0x647fa60; // 0x64575b0
	constexpr uintptr_t localplayer_offset = 0x6467fb0;
	constexpr uintptr_t viewMatrix = 0x63b7080;

	namespace cgame_offsets
	{
		constexpr uintptr_t ballistics_offset = 0x408;
		constexpr uintptr_t camera_offset = 0x5e8;
		namespace camera_offsets
		{
			constexpr uintptr_t camera_matrix_offset = 0x1c0;
			//constexpr uintptr_t camera_position_offset = 0x0; // FAILED TO GRAB
		}
		namespace ballistic_offsets
		{
			constexpr uintptr_t selected_unit_ptr = 0x690;//Ballistics + 0x668
			constexpr uintptr_t weapon_position_two = 0x1EE0 + 0x20;//Ballistics + 0x1EE0 + 0x20
			constexpr uintptr_t velocity = 0x1F10;//Ballistics + 0x1F10
			constexpr uintptr_t mass = 0x1F1C;//Ballistics + 0x1F1C
			constexpr uintptr_t caliber = 0x1F20;//Ballistics + 0x1F20
			constexpr uintptr_t length = 0x1F24;//Ballistics + 0x1F24
			constexpr uintptr_t max_dist = 0x1F28;//Ballistics + 0x1F28
			constexpr uintptr_t bomb_impact_point = 0x1AEC + 0x20;//Ballistics + 0x1AEC + 0x20
			constexpr uintptr_t bullet_impact_point = 0x22C8 + 0x20;//Ballistics + 0x22C8 + 0x20
			constexpr uintptr_t ingame_ballistics = 0x2328;//Ballistics + 0x2320 + 0x20
			constexpr uintptr_t weapon_position = 0x1F00;//Ballistics + 0x1F00

			constexpr uintptr_t telecontrol_offset = 0xc68;
			namespace telecontrol_offsets
			{
				constexpr uintptr_t gameui_offset = 0x700;
				namespace gameui_offsets
				{
					//constexpr uintptr_t mousepos_offset = 0x0; // FAILED TO GRAB
				}
			}
		}
	}

	namespace localplayer
	{
		constexpr uintptr_t Rerept_offset = 0x78;
		constexpr uintptr_t brokenSlots_offset = 0x558;
		constexpr uintptr_t cachedIsAutoSquad_offset = 0xc98;
		constexpr uintptr_t clanTag_offset = 0x170;
		constexpr uintptr_t classinessMark_offset = 0x5f8;
		constexpr uintptr_t controlledUnitRef_offset = 0x8f0;
		constexpr uintptr_t countryId_offset = 0x238;
		constexpr uintptr_t customState_offset = 0x298;
		constexpr uintptr_t decals_offset = 0x1e8;
		constexpr uintptr_t disabledByMatchingSlots_offset = 0x528;
		constexpr uintptr_t dummyForCountUsedSlots_offset = 0x730;
		constexpr uintptr_t dummyForCrewUnitsList_offset = 0x4f8;
		constexpr uintptr_t dummyForFootballStat_offset = 0xbf8;
		constexpr uintptr_t dummyForKillStreaksProgress_offset = 0x810;
		constexpr uintptr_t dummyForPlayerStat_offset = 0xbc8;
		constexpr uintptr_t dummyForRoundScore_offset = 0xa38;
		constexpr uintptr_t dummyForSpawnCosts_offset = 0x770;
		constexpr uintptr_t dummyForSpawnDelayTimes_offset = 0x7b0;
		constexpr uintptr_t dummyForSupportPlanes_offset = 0x428;
		constexpr uintptr_t forceLockTarget_offset = 0xc70;
		constexpr uintptr_t forcedRespawn_offset = 0x678;
		constexpr uintptr_t guiState_offset = 0x6c8;
		constexpr uintptr_t invitedNickName_offset = 0x120;
		constexpr uintptr_t localunit_offset = 0x8c0;
		constexpr uintptr_t memberId_offset = 0x260;
		constexpr uintptr_t missionSupportUnitEnabled_offset = 0xd40;
		constexpr uintptr_t missionSupportUnitRef_offset = 0xd10;
		constexpr uintptr_t nickFrame_offset = 0xce8;
		constexpr uintptr_t nickLocKey_offset = 0x148;
		constexpr uintptr_t ownedSlots_offset = 0x5d0;
		constexpr uintptr_t ownedUnitRef_offset = 0x8c0;
		constexpr uintptr_t publicFlags_offset = 0x1c0;
		constexpr uintptr_t rageTokens_offset = 0xd68;
		constexpr uintptr_t realNick_offset = 0xc20;
		constexpr uintptr_t roundAiGroundKills_offset = 0xb50;
		constexpr uintptr_t roundAiKills_offset = 0xb28;
		constexpr uintptr_t roundAiNavalKills_offset = 0xb78;
		constexpr uintptr_t roundDeaths_offset = 0xab0;
		constexpr uintptr_t roundFriendlyKills_offset = 0xa88;
		constexpr uintptr_t roundGroundKills_offset = 0xad8;
		constexpr uintptr_t roundKills_offset = 0xa60;
		constexpr uintptr_t roundNavalKills_offset = 0xb00;
		constexpr uintptr_t spareAircraftInSlots_offset = 0x5a8;
		constexpr uintptr_t spectatedModelIndex_offset = 0x6f0;
		constexpr uintptr_t squadScore_offset = 0x868;
		constexpr uintptr_t squadronId_offset = 0xc48;
		constexpr uintptr_t supportUnitRef_offset = 0x930;
		constexpr uintptr_t timeToKick_offset = 0x6a0;
		constexpr uintptr_t timeToRespawnInCoop_offset = 0x650;
		constexpr uintptr_t timeToRespawn_offset = 0x628;
		constexpr uintptr_t wasReadySlots_offset = 0x580;
		constexpr uintptr_t wreckedPartShipUnitRef_offset = 0x960;
	}

	namespace unit_offsets
	{

		constexpr uintptr_t ground_velocity_offset = 0x54;
		constexpr uintptr_t airmovement_offset = 0x10;
		constexpr uintptr_t allowBailout_offset = 0xa80;
		constexpr uintptr_t bbmax_offset = 0x22c;
		constexpr uintptr_t bbmin_offset = 0x220;
		constexpr uintptr_t bombDelayExplosion_offset = 0x8e8;
		constexpr uintptr_t briefMalfunctionState_offset = 0x8c0;
		constexpr uintptr_t brokenPropFlags_offset = 0x2e98;
		constexpr uintptr_t brokenTurretDriveJammedTime_offset = 0x600;
		constexpr uintptr_t brokenTurretDriveMult_offset = 0x650;
		constexpr uintptr_t brokenTurretDriveSpeed_offset = 0x628;
		constexpr uintptr_t curNightVisionMode_offset = 0x710;
		constexpr uintptr_t default_offset = 0x1b78;
		constexpr uintptr_t delayWithFlightTime_offset = 0x910;
		constexpr uintptr_t dummyForDeathInfo_offset = 0x998;
		constexpr uintptr_t dummyForUnitFlags_offset = 0xcc8;
		constexpr uintptr_t dummyVarForCrewLayout_offset = 0x740;
		constexpr uintptr_t dummyVarForMissionAddText_offset = 0x768;
		constexpr uintptr_t enableGunners_offset = 0xc68;
		constexpr uintptr_t extThrustMult_offset = 0x3cc0;
		constexpr uintptr_t extinguishAssistant_offset = 0xbc8;
		constexpr uintptr_t extinguishAssistee_offset = 0xb98;
		constexpr uintptr_t farthestExitZoneId_offset = 0xd70;
		constexpr uintptr_t fuseModeIndex_offset = 0x16b8;
		constexpr uintptr_t groundmovement_offset = 0x1ab8;
		constexpr uintptr_t hasModuleEffectsToRepair_offset = 0x6a0;
		constexpr uintptr_t ignoreCollisionDamage_offset = 0x3d80;
		constexpr uintptr_t info_offset = 0xdc0;
		constexpr uintptr_t invulnerable_offset = 0xc40;
		constexpr uintptr_t isAlternativeShotFreq_offset = 0x1c8;
		constexpr uintptr_t isBreechDamaged_offset = 0x678;
		constexpr uintptr_t isNeedExtinguishHelp_offset = 0x15d8;
		constexpr uintptr_t isNeedRepairHelp_offset = 0x15a8;
		constexpr uintptr_t isOnAirfieldAndCanRearmedVal_offset = 0x3560;
		constexpr uintptr_t killer_offset = 0x14d8;
		constexpr uintptr_t lastBuildingTime_offset = 0x870;
		constexpr uintptr_t lastContactFrom_offset = 0x9d0;
		constexpr uintptr_t lastContactTimeRel_offset = 0xa58;
		constexpr uintptr_t lastContactTime_offset = 0xa30;
		constexpr uintptr_t lastContactTo_offset = 0xa00;
		constexpr uintptr_t lowRateUnitFlags_offset = 0xcf8;
		constexpr uintptr_t maskingFactor_offset = 0x1658;
		constexpr uintptr_t moduleEffectsRepairAtTime_offset = 0x6c8;
		constexpr uintptr_t nextUseArtilleryTime_offset = 0x13c0;
		constexpr uintptr_t persistentAerobaticsSmokeId_offset = 0x2e70;
		constexpr uintptr_t persistentAerobaticsSmoke_offset = 0x2e48;
		constexpr uintptr_t position_offset = 0xAE0;
		constexpr uintptr_t prepareExtinguishAssistantTime_offset = 0x1350;
		constexpr uintptr_t prepareRepairAssistantTime_offset = 0x1328;
		constexpr uintptr_t prepareRepairAssisteeTime_offset = 0x1300;
		constexpr uintptr_t prepareRepairCooldownsTime_offset = 0x1478;
		constexpr uintptr_t repairAssistant_offset = 0xb68;
		constexpr uintptr_t repairAssistee_offset = 0xb38;
		constexpr uintptr_t repairCooldowns_offset = 0x1608;
		constexpr uintptr_t repairTimer_offset = 0x1a68;
		constexpr uintptr_t rocketFuseDist_offset = 0x938;
		constexpr uintptr_t rotation_matrix_offset = 0xac4;
		constexpr uintptr_t scoutCooldown_offset = 0xff0;
		constexpr uintptr_t scoutStartTime_offset = 0xfc8;
		constexpr uintptr_t smokeScreenActived_offset = 0x1758;
		constexpr uintptr_t smokeScreenCount_offset = 0x1730;
		constexpr uintptr_t stealthArmyMask_offset = 0xe38;
		constexpr uintptr_t stealthRadiusSq_offset = 0xe10;
		constexpr uintptr_t supportPlaneCatapultsFuseMask_offset = 0x838;
		constexpr uintptr_t supportPlanesCount_offset = 0x810;
		constexpr uintptr_t timeRepair_offset = 0x1a40;
		constexpr uintptr_t timeToNextSmokeScreen_offset = 0x1708;
		constexpr uintptr_t timeToRearm_offset = 0x1a90;
		constexpr uintptr_t timeToRefuel_offset = 0x3ce8;
		constexpr uintptr_t timeToSurrender_offset = 0x3d10;
		constexpr uintptr_t torpedoDiveDepth_offset = 0x960;
		constexpr uintptr_t turret_offset = 0xe68;
		constexpr uintptr_t unitArmyNo_offset = 0xdb0;
		constexpr uintptr_t unitState_offset = 0xd20;
		constexpr uintptr_t visualReloadProgress_offset = 0x898;
		constexpr uintptr_t vulnerableByUnitUId_offset = 0xc98;
		constexpr uintptr_t wingBreakRnd_offset = 0x2ec0;
	}

}
