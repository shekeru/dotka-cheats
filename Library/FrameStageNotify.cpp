#include "stdafx.h"
#include "hooks.h"
#include <iterator> 
std::vector<CDotaBaseNPC*> in_range = {};

void SDK::FrameStageNotify(CSource2Client* ecx, ClientFrameStage_t stage) {
	CDotaBaseNPC* best;
	switch (stage) {
	case ClientFrameStage_t::FRAME_START:
		break;
	case ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_END:
		break;
	case ClientFrameStage_t::FRAME_RENDER_END:
		if (!sdk.LocalHero) break;
		std::copy_if(sdk.Creeps.begin(), sdk.Creeps.end(), 
			std::back_inserter(in_range), [](CDotaBaseNPC* x) {
			return sdk.LocalHero->GetAttackRange() > (*x->GetNetworkOrigin()
				- *sdk.LocalHero->GetNetworkOrigin()).Length2D() && 
			x->GetHealth() * x->GetBaseArmor() <= sdk.LocalHero->GetDamageMin();
		}); 
		best = *std::min_element(in_range.begin(), in_range.end(), [](CDotaBaseNPC* a, CDotaBaseNPC* b) {
			return a->GetHealth() * a->GetBaseArmor()
				> b->GetHealth() * b->GetBaseArmor();
		}); if (best) printf("go hit %p\n", best);
		in_range.clear(); break;
	default:
		break;
	}; vmt.client->GetOriginalMethod(FrameStageNotify)(ecx, stage);
}