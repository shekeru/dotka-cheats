#include "hooks.h"

CDotaBaseNPC* ReAttack()
{
	std::vector<CDotaBaseNPC*> in_range = {};
	// Reduce to Valid Creeps
	std::copy_if(sdk.Creeps.begin(), sdk.Creeps.end(),
		std::back_inserter(in_range), [](CDotaBaseNPC* x) {
		return x->IsInRange(sdk.LocalHero) &&
			x->CanLastHit(sdk.LocalHero);
	});
	// Select best
	auto best = std::min_element(in_range.begin(), in_range.end(), [](auto a, auto b) {
		return a->GetHealth() > b->GetHealth();
	}); 
	if (best < in_range.end()) {
		printf("CreepTable Size: %d, Lowest Health: %d\n", in_range.size(), (*best)->GetHealth());
		return *best;
	} else return nullptr;
};

void SDK::PrepareUnitOrders(CDotaPlayer *ecx, DotaUnitOrder_t order, int targetIndex, Vector movePosition, 
	int abilityIndex, PlayerOrderIssuer_t orderIssuer, CDotaBaseNPC *entity, bool queue, 
		OrderQueueBehavior_t queueBehavior, bool showEffects) 
{
	static auto prepareOrder = vmt.player->GetOriginalMethod(PrepareUnitOrders);
	// Custom Orders
	printf("ShitOrder: (%d) %p -- %d, %d\n", targetIndex, entity, queueBehavior, queue);
	if (order == DOTA_UNIT_ORDER_MOVE_TO_POSITION) {
		if (entity = ReAttack());
			//return prepareOrder(ecx, DOTA_UNIT_ORDER_ATTACK_TARGET, targetIndex, movePosition, 
				//abilityIndex, orderIssuer, entity, queue, queueBehavior, false);
	} prepareOrder(ecx, order, targetIndex, movePosition, abilityIndex, 
		orderIssuer, entity, queue, queueBehavior, showEffects);
}