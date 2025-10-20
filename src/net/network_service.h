#pragma once

#include <vector>
#include <string>
#include <memory>
#include <map>
#include "../block.h" // Includes CBlock, CBlockHeader
#include "p2p_message.h" // Includes CNetMessage

namespace ORPH::Net {

/**
 * @brief Represents a single connection to a peer node.
 * This structure holds state information for active connections.
 */
struct PeerConnection {
    uint32_t socket_id = 0;             // Unique identifier for the socket/connection
    std::string ip_address;             // IPv4 or IPv6 address of the peer
    uint16_t port = 0;                  // Port number of the peer
    uint64_t last_activity_time = 0;    // Timestamp of the last received message
    uint32_t version = 0;               // Protocol version of the peer
    bool is_inbound = false;            // True if this is an incoming connection
    bool is_ready = false;              // True after successful version handshake
};

/**
 * @brief The NetworkService class manages all P2P connections, message sending,
 * and block/transaction synchronization.
 */
class NetworkService {
public:
    NetworkService();
    ~NetworkService();

    /**
     * @brief Initializes the node and starts listening for incoming connections.
     * @param port The port number to listen on.
     * @return True if the service started successfully.
     */
    bool Start(uint16_t port);

    /**
     * @brief Attempts to connect to a specific remote peer.
     * @param ip_address The target IP address.
     * @param port The target port number.
     * @return True if the connection attempt was successful.
     */
    bool ConnectToPeer(const std::string& ip_address, uint16_t port);

    /**
     * @brief Shuts down all connections and the listening socket.
     */
    void Shutdown();

    /**
     * @brief Broadcasts a newly mined or newly validated block to all connected peers.
     * This is critical for propagating the Block-DAG structure.
     * @param block The CBlock object to broadcast.
     */
    void BroadcastBlock(const ORPH::Core::CBlock& block);

    /**
     * @brief Sends a new transaction to the network.
     * @param tx The CTransaction object to broadcast.
     */
    void BroadcastTransaction(const ORPH::Core::CTransaction& tx);

    /**
     * @brief Main network processing loop to handle incoming and outgoing messages.
     */
    void RunMainLoop();

private:
    std::map<uint32_t, PeerConnection> peers_; // Map of active connections
    uint16_t listening_port_ = 0;

    /**
     * @brief Handles a message received from a specific peer.
     * This method will call the relevant Consensus or Transaction logic based on the message type.
     * @param peer_id The ID of the peer that sent the message.
     * @param message The parsed network message object.
     */
    void HandleMessage(uint32_t peer_id, const CNetMessage& message);

    /**
     * @brief Attempts to read data from a socket and processes it into a CNetMessage.
     * @param socket_id The socket to read from.
     * @return The parsed message, or an invalid message if parsing fails.
     */
    CNetMessage ReadMessage(uint32_t socket_id);
};

} // namespace ORPH::Net
