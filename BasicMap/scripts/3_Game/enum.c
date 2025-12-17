enum BASICMAPRPCs
{
	RPC_BASICMAP_START = 215132,
	SEND_MARKERS,
	SAVE_MARKERS,
	REQUEST_MARKERS
}

// Marker visibility modes for cycling with K key
enum BasicMapVisibilityMode
{
	SHOW_ALL = 0,         // Show all markers (server + local/groups)
	SERVER_ONLY = 1,      // Show only server config markers
	LOCAL_ONLY = 2,       // Show only local markers and other groups
	HIDE_ALL = 3          // Hide all markers
}