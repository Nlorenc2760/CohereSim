/// @file mosi.h
/// @brief Declaration of the MOSI coherence protocol

#pragma once

#include "coherence_protocol.h"

/// @brief The MOSI coherence protocol
class MOSI : public CoherenceProtocol {
public:

    /// @brief Construct a new MOSI coherence protocol
    /// @param cache The parent cache
    MOSI(Cache& cache) : CoherenceProtocol(cache) {}

    /// @brief Receive a PrRd message
    /// @param line The cache line accessed (non-null)
    void PrRd(cache_line* line);
    /// @brief Receive a PrWr message
    /// @param line The cache line accessed (non-null)
    void PrWr(cache_line* line);

    /// @brief Receive a BusRd message
    /// @param line The cache line accessed
    /// @return True if the line data can be or could have been shared
    bool BusRd(cache_line* line);
    /// @brief Receive a BusRdX message
    /// @param line The cache line accessed
    /// @return True if the line data can be or could have been shared
    bool BusRdX(cache_line* line);
    /// @brief Receive a BusUpgr message
    /// @param line The cache line accessed
    /// @return True if the line data can be or could have been shared
    bool BusUpgr(cache_line* line);

    /// @brief Determine whether the coherence protocol does dirty sharing
    /// @return True if the coherence protocol does dirty sharing
    bool doesDirtySharing();

    /// @brief Determine whether a line needs to be written back to main memory
    /// @param state The state of the line
    /// @return Whether the line needs to be written back to main memory
    bool isWriteBackNeeded(state_e state);
};
