#include "stdafx.h"
#include "hooks.h"

void SDK::FrameStageNotify(CSource2Client* ecx, ClientFrameStage_t stage) {
	switch (stage) {
	case ClientFrameStage_t::FRAME_START:
		break;
	case ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_END:
		break;
	case ClientFrameStage_t::FRAME_RENDER_END:
		break;
	default:
		break;
	}; vmt.client->GetOriginalMethod(FrameStageNotify)(ecx, stage);
}