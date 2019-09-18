#pragma once
#include "vector.h"

enum OverlayFlags_t : unsigned long long
{
	BBOX = (1 << 2), //4
	ABSBOX = (1 << 5),//32
	RBOX = (1 << 6), //64
	ENTITYBOUNDS = (1 << 7), //128 - Looks like it depends on a byte being set in the class.
	ENTITYATTACHMENTS = (3 << 8), //BYTE1(flags) & 3
	ENTITYJOINTINFO = 0x40000,
	ENTITYSKELETON = (24 << 8), //BYTE1(flags) & 24 // kinda slow.
	ENTITYHITBOXES = (192 << 8), //BYTE1(flags) & 192
	BUDDHA = 0x40000000,
	ENTITYVIEWOFFSET = 0x800000000
};

enum DOTATeam_t : int {
	DOTA_TEAM_INVALID = -1,
	DOTA_TEAM_FIRST = 2,
	DOTA_TEAM_GOODGUYS = 2, //Radiant team.
	DOTA_TEAM_BADGUYS = 3, 	//Dire team.
	DOTA_TEAM_NEUTRALS = 4, //Neutral.
	DOTA_TEAM_NOTEAM = 5,
	DOTA_TEAM_CUSTOM_1 = 6,
	DOTA_TEAM_CUSTOM_MIN = 6,
	DOTA_TEAM_CUSTOM_2 = 7,
	DOTA_TEAM_CUSTOM_3 = 8,
	DOTA_TEAM_CUSTOM_COUNT = 8,
	DOTA_TEAM_CUSTOM_4 = 9,
	DOTA_TEAM_CUSTOM_5 = 10,
	DOTA_TEAM_CUSTOM_6 = 11,
	DOTA_TEAM_CUSTOM_7 = 12,
	DOTA_TEAM_CUSTOM_8 = 13,
	DOTA_TEAM_CUSTOM_MAX = 13,
	DOTA_TEAM_COUNT = 14
};

#include "Datamap.h"
#include "CEntityInstance.h"
#include "CSource2Client.h"
#define SpatializationInfo_t char
#define IPhysicsObject char
#define CCollisionProperty char

class CBaseEntity : public CEntityInstance
{
public:
	inline int FindDataMapElementOffset(const char *element, Datamap* dMap = 0) {
		if(dMap == nullptr) dMap = this->GetPredDescMap();
		while (dMap) {
			for (uint64_t i = 0; i < dMap->numFields; i++) {
				if (!dMap->dataDesc[i].fieldName)
					continue;

				if (!strcmp(dMap->dataDesc[i].fieldName, element))
					return dMap->dataDesc[i].fieldOffset[TD_OFFSET_NORMAL];

				if (dMap->dataDesc[i].type == FIELD_EMBEDDED) {
					if (dMap->dataDesc[i].td) {
						int temp = FindDataMapElementOffset(element, dMap->dataDesc[i].td);
						if (temp != 0)
							return temp;
					}
				}
			}
			dMap = dMap->baseMap;
		}
		return 0;
	}
	inline Vector* const GetNetworkOrigin()
	{
		static int offset = FindDataMapElementOffset("m_vecNetworkOrigin");
		if (!offset) {
			printf("[ERROR] NetworkOrigin offset is Zero!\n");
			return NULL;
		}; return (Vector*)(((uintptr_t)this) + offset);
	}
	// Virtual Funcs
	virtual Datamap* GetPredDescMap(); // 26, 
	virtual CCollisionProperty* GetCollideable(); // 27, 
	virtual void GetPredictionCopyable(); // 28, 
	virtual void YouForgotToImplementOrDeclareClientClass(); // 29, 
	virtual ClientClass* GetClientClass(); // 30, 
	virtual void SpawnShared(); // 31, 
	virtual void PopulatePoseParameters(); // 32, 
	virtual void PreFirstNetworkUpdate(); // 33, 
	virtual void GetBaseModelEntity(); // 34, 
	virtual void GetBaseAnimating(); // 35, 
	virtual void n_36(); // 36, 
	virtual void n_37(); // 37, 
	virtual void Classify(); // 38, 
	virtual void ModifyEconParticles(); // 39, 
	virtual void ShouldSavePhysics(); // 40, 
	virtual void GetShadowDrawMaterial(); // 41, 
	virtual bool IsAbleToHaveFireEffect(); // 42, 
	virtual bool IsSelectable(); // 43, 
	virtual bool ReceivesMouseoverButNotSelection(); // 44, 
	virtual float GetRingRadius(); // 45, 
	virtual void UpdateFlexControllers(); // 46, 
	virtual void SetupWeights(); // 47, 
	virtual void GetVectors(); // 48, 
	virtual void WorldAlignMins(); // 49, 
	virtual void WorldAlignMaxs(); // 50, 
	virtual void WorldSpaceCenter(); // 51, 
	virtual void ComputeWorldSpaceSurroundingBox(); // 52, 
	virtual void UpdateTransmitState(); // 53, 
	virtual void ValidateModelIndex(); // 54, 
	virtual void AsParticleEHandle(); // 55, 
	virtual void OnNewParticleEffect(); // 56, 
	virtual void OnParticleEffectDeleted(); // 57, 
	virtual void PredCopy_SetHeapSize(); // 58, 
	virtual void PredCopy_GetStructBase(); // 59, 
	virtual void PredCopy_GetOffsetType(); // 60, 
	virtual void PredCopy_SetCommand(); // 61, 
	virtual void PredCopy_GetCommand(); // 62, 
	virtual void PredCopy_Alloc(); // 63, 
	virtual void PredCopy_Tell(); // 64, 
	virtual void PredCopy_GetHeaderBlock(); // 65, 
	virtual void GetMouth(); // 66, 
	virtual void GetSoundSpatialization(); // 67, 
	virtual void LookupAttachment(const char* name); // 68, 
	virtual void GetAttachment(unsigned char, matrix3x4_t &); // 69, 
	virtual void InvalidateAttachments(); // 70, 
	virtual void OnBoneTransformsChanged(); // 71, 
	virtual void ChangeTeam(DOTATeam_t team); // 72, 
	virtual bool InSameTeam(CBaseEntity *other); // 73, 
	virtual bool InLocalTeam(void); // 74, 
	virtual void DrawDebugTextOverlays(); // 75, 
	virtual bool IsValidIDTarget(); // 76, 
	virtual const char* GetIDString(); // 77, 
	virtual bool IsPotentiallyUsable(); // 78, 
	virtual const char* GetUseString(); // 79, 
	virtual void IsAbleToGlow(); // 80, 
	virtual void GetUseType(); // 81, 
	virtual void* GetGlowEntity(); // 82, 
	virtual void IsSaveNonNetworkable(); // 83, 
	virtual void UpdateVisibility(); // 84, 
	virtual void ShouldDraw(); // 85, 
	virtual void Simulate(); // 86, 
	virtual void FrameSimulate(); // 87, 
	virtual void n_88(); // 88, 
	virtual void OnDataChanged(); // 89, 
	virtual void OnPreDataChanged(); // 90, 
	virtual void ShouldTransmit(); // 91, 
	virtual void GetClientVehicle(); // 92, 
	virtual void OverrideAlphaModulation(); // 93, 
	virtual void OverrideShadowAlphaModulation(); // 94, 
	virtual void ComputeClientSideReplacementModel(); // 95, 
	virtual void Interpolate(); // 96, 
	virtual void CreateLightEffects(); // 97, 
	virtual void Clear(); // 98, 
	virtual void GetTextureAnimationStartTime(); // 99, 
	virtual void TextureAnimationWrapped(); // 100, 
	virtual void ShadowCastType(); // 101, 
	virtual void ShouldReceiveProjectedTextures(); // 102, 
	virtual void AddDecal(); // 103, 
	virtual void OnTakeDamage(); // 104, 
	virtual void TakeDamage(); // 105, 
	virtual void n_106(); // 106, 
	virtual void n_107(); // 107, 
	virtual void n_108(); // 108, 
	virtual void n_109(); // 109, 
	virtual void n_110(); // 110, 
	virtual void n_111(); // 111, 
	virtual void GetPredictionOwner(); // 112, 
	virtual void n_113(); // 113, 
	virtual void InitPredictable(); // 114, 
	virtual void SetPredictable(bool); // 115, 
	virtual void DecalTrace(); // 116, 
	virtual void ImpactTrace(); // 117, 
	virtual bool ShouldPredict(); // 118, 
	virtual void PreRender(); // 119, 
	virtual const char* CBE_PlayerName(); // 120, 
	virtual void GetUsePriority(); // 121, 
	virtual void EstimateAbsVelocity(); // 122, 
	virtual void CanBePoweredUp(); // 123, 
	virtual void AttemptToPowerup(); // 124, 
	virtual void IsCurrentlyTouching(); // 125, 
	virtual void ClientThink(); // 126, 
	virtual void GetThinkHandle(); // 127, 
	virtual void SetThinkHandle(); // 128, 
	virtual void SetNextClientThink(); // 129, 
	virtual void PhysicsSimulate(); // 130, 
	virtual void SimulateThinkInterval(); // 131, 
	virtual void PhysicsSolidMaskForEntity(); // 132, 
	virtual void* ClothGetEntityInstanceSettings(); // 133, 
	virtual void NotifySystemEvent(); // 134, 
	virtual void SUB_Remove(); // 135, 
	virtual void ExtraSceneObjectUpdater(); // 136, 
	virtual void FireBullets(); // 137, RagdollImpact
	virtual void DoImpactEffect(); // 138, 
	virtual void MakeTracer(); // 139, 
	virtual void GetTracerAttachment(); // 140, 
	virtual void GetTracerType(); // 141, 
	virtual void GetBeamTraceFilter(); // 142, 
	virtual void DispatchTraceAttack(); // 143, 
	virtual void TraceAttack(); // 144, 
	virtual void n_145(); // 145, 
	virtual bool ShouldDrawWaterImpacts(); // 146, 
	virtual bool ShouldDrawUnderwaterBulletBubbles(); // 147, 
	virtual void HandleShotImpactingWater(); // 148, STR: gunshotsplash
	virtual void BloodColor(); // 149, 
	virtual void n_150(); // 150, 
	virtual bool IsPlayer(); // 151, 
	virtual bool IsHMDAvatar(); // 152, 
	virtual void n_153(); // 153, 
	virtual bool IsBaseCombatCharacter(); // 154, 
	virtual void* MyCombatCharacterPointer(); // 155, 
	virtual void* MyCombatCharacterPointer2(); // 156, 
	virtual bool IsBaseCombatWeapon(); // 157, 
	virtual void* MyCombatWeaponPointer(); // 158, 
	virtual bool IsBaseObject(); // 159, 
	virtual bool IsBaseTrain(); // 160, 
	virtual bool IsNextBot(); // 161, 
	virtual void* MyInfectedPointer(); // 162, 
	virtual void* MyInfectedRagdollPointer(); // 163, 
	virtual bool IsSprite(); // 164, 
	virtual int GetMaxHealth(); // 165, 
	virtual void SetHealth(int); // 166, 
	virtual int GetHealth(); // 167, 
	virtual int GetActualHealth(); // 168, 
	virtual void ModifyOrAppendCriteria(); // 169, 
	virtual void WantSpawnCallOnPreData(); // 170, 
	virtual Vector* EyePosition(); // 171, 
	virtual void EyeAngles(); // 172, 
	virtual void LocalEyeAngles(); // 173, 
	virtual void EarPosition(); // 174, 
	virtual void GetFriction(); // 175, 
	virtual void GetViewOffset(); // 176, 
	virtual void GetSmoothedVelocity(); // 177, 
	virtual void GetVelocity(); // 178, 
	virtual void IsMoving(); // 179, 
	virtual void OnGroundChanged(); // 180, 
	virtual void GetGroundVelocityToApply(); // 181, 
	virtual void GetAttackDamageScale(); // 182, 
	virtual void InternalSetEffects(); // 183, 
	virtual void ShouldInterpolate(); // 184, 
	virtual void GetS1Skin(); // 185, 
	virtual void BoneMergeFastCullBloat(); // 186, 
	virtual void GetAimEntOrigin(); // 187, 
	virtual void SetupBones(); // 188, 
	virtual void AddRagdollToFadeQueue(); // 189, 
	virtual void OnLeftClick(); // 190, 
	virtual void OnRightClick(); // 191, 
	virtual void OnCursorEntered(); // 192, 
	virtual void OnCursorExited(); // 193, 
	virtual void GetSelection(); // 194, 
	virtual void GenericSelectionGetClickValidBehaviors(); // 195, 
	virtual void PerformCustomPhysics(); // 196, 
	virtual Vector* GetRenderOrigin(); // 197, 
	virtual void GetRenderAngles(); // 198, 
	virtual void GetObserverCamOrigin(); // 199, 
	virtual void RenderableToWorldTransform(); // 200, 
	virtual void DrawModel(); // 201, 
	virtual void GetRenderBounds(); // 202, 
	virtual void GetRenderBoundsWorldspace(); // 203, 
	virtual void Spawn(); // 204, 
	virtual void Precache(); // 205, 
	virtual void SetDormant(); // 206, 
	virtual void KeyValue(); // 207, 
	virtual void GetKeyValue(); // 208, 
	virtual void Release(); // 209, 
	virtual void OnParseMapDataFinished(); // 210, 
	virtual void NotifyShouldTransmit(); // 211, 
};