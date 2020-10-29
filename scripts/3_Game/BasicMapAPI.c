class BasicMapAPI {
    private static ref BasicMapAPI basicMapAPI;

    static BasicMapAPI Get () {
        if (!basicMapAPI) {
            basicMapAPI = new ref BasicMapAPI;
        }
        return basicMapAPI;
    }

    private ref BasicMapController controller;

    private void BasicMapAPI () {
        controller = BasicMap ();
    }

    void RegisterGroup (string group) {
        //TODO if we want something to change based on whether
        //     a group is registered or not
    }

    ref array<ref BasicMapMarker> GetGroupMarkers (string group) {
        return controller.GetMarkers (group);
    }

    void AddGroupMarker (string group, BasicMapMarker marker) {
        controller.AddMarker (group, marker);
        OnGroupChanged (group);
    }

    void ClearGroup (string group) {
        controller.RemoveAllMarkers (group);
        OnGroupChanged (group);
    }

    void OnGroupChanged (string group) {
        // Users should override this callback for their purposes
    }

}