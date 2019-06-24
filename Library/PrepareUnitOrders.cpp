#include "hooks.h"

void SDK::PrepareUnitOrders(CDotaPlayer *ecx, DotaUnitOrder_t order, int targetIndex, Vector movePosition, int abilityIndex, PlayerOrderIssuer_t orderIssuer,
	CDotaBaseNPC *entity, bool queue, OrderQueueBehavior_t queueBehavior, bool showEffects) {
	return vmt.player->GetOriginalMethod(PrepareUnitOrders)(ecx, order, targetIndex, movePosition, 
		abilityIndex, orderIssuer, entity, queue, queueBehavior, showEffects);
}