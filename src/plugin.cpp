#if defined(WIN32) || defined(__WIN32__) || defined(_WIN32)
#pragma warning(disable : 4100) /* Disable Unreferenced parameter warning */
#include <Windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "teamspeak/public_errors.h"
#include "teamspeak/public_errors_rare.h"
#include "teamspeak/public_definitions.h"
#include "teamspeak/public_rare_definitions.h"
#include "teamspeak/clientlib_publicdefinitions.h"
#include "ts3_functions.h"

#include "plugin.h"
#include "definitions.hpp"
#include "helper.h"

static struct TS3Functions ts3Functions;
static char *pluginID = NULL;

/*-------------------------- Plugin Information --------------------------*/

#define PLUGIN_NAME        "StateMC Mover"
#define PLUGIN_VERSION     "1.0"
#define PLUGIN_AUTHOR      "Your Name"
#define PLUGIN_DESCRIPTION "Description of StateMC Mover"

/*-------------------------- Initialize & Shutdown -----------------------*/

int ts3plugin_init() {
    // Initialization code here (if needed)
    return 0;
}

void ts3plugin_shutdown() {
    // Shutdown code here (if needed)
    if (pluginID) {
        free(pluginID);
        pluginID = NULL;
    }
}

/*-------------------------- Required Functions --------------------------*/

const char* ts3plugin_name() {
    return PLUGIN_NAME;
}

const char* ts3plugin_version() {
    return PLUGIN_VERSION;
}

int ts3plugin_apiVersion() {
    return PLUGIN_API_VERSION;
}

const char* ts3plugin_author() {
    return PLUGIN_AUTHOR;
}

const char* ts3plugin_description() {
    return PLUGIN_DESCRIPTION;
}

void ts3plugin_setFunctionPointers(const struct TS3Functions funcs) {
    ts3Functions = funcs;
}

int ts3plugin_offersConfigure() {
    // Change this to return the appropriate value if your plugin offers configuration
    return PLUGIN_OFFERS_NO_CONFIGURE;
}

void ts3plugin_registerPluginID(const char* id) {
    const size_t sz = strlen(id) + 1;
    pluginID = (char*)malloc(sz * sizeof(char));
    _strcpy(pluginID, sz, id);
}

void ts3plugin_freeMemory(void* data) {
    free(data);
}

void moveToChannel180(uint64 serverConnectionHandlerID) {
    anyID clientID;
    uint64 newChannelID = 180; // Channel ID set to 180

    // Retrieve the current client ID
    if(ts3Functions.getClientID(serverConnectionHandlerID, &clientID) != ERROR_ok) {
        printf("Error retrieving client ID\n");
        return;
    }

    // Request to move the client to the specified channel
    ts3Functions.requestClientMove(serverConnectionHandlerID, clientID, newChannelID, "", NULL);
}
