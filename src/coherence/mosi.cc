/// @file mosi.cc
/// @brief Implementation of the MOSI coherence protocol

#include "mosi.h"

ADD_COHERENCE_TO_CMD_LINE(MOSI);

void MOSI::PrRd(cache_line* line) {
    switch (line->state) {
    case M:
    case O:
    case S:
        break;
    case I:
        cache.issueBusMsg(BusRead);
        line->state = S;
        break;
    default:
        STATE_ERR;
        return;
    }
}

void MOSI::PrWr(cache_line* line) {
    switch (line->state) {
    case M:
        break;
    case O:
    case S:
        cache.issueBusMsg(BusUpgrade);
        line->state = M;
        break;
    case I:
        cache.issueBusMsg(BusReadX);
        line->state = M;
        break;
    default:
        STATE_ERR;
        return;
    }
}

bool MOSI::BusRd(cache_line* line) {
    switch (line->state) {
    case M:
        line->state = O;
    case O:
        return true;
    case S:
    case I:
        return false;
    default:
        STATE_ERR;
        return false;
    }
}

bool MOSI::BusRdX(cache_line* line) {
    switch (line->state) {
    case M:
    case O:
        line->state = I;
        return true;
    case S:
        line->state = I;
    case I:
        return false;
    default:
        STATE_ERR;
        return false;
    }
}

bool MOSI::BusUpgr(cache_line* line) {
    switch (line->state) {
    case O:
    case S:
        line->state = I;
    case I:
        return false;
    case M:
    default:
        STATE_ERR;
        return false;
    }
}

bool MOSI::doesDirtySharing() {
    return true;
}

bool MOSI::isWriteBackNeeded(state_e state) {
    if(state == M || state == O)
        return true;
    else
    return false;
}
