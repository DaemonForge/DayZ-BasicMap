class BasicMapAPIExample {
    static const string EXAMPLE_GROUP = "ExampleGroup";

    static void SomeFunction (string name, vector position) {
        auto api = BasicMapAPI.Get ();
        api.AddGroupMarker (EXAMPLE_GROUP, new BasicMapAPIMarker (name, position));
    }

    static void SomeOtherFunction () {
        Print (EXAMPLE_GROUP + " has changed");
    }

    static void SomeThirdFunction () {
        Print ("Client markers have changed");
    }

}

modded class BasicMapAPI {
    override void OnGroupChanged (string group) {
        switch (group) {
            case BasicMapAPIExample.EXAMPLE_GROUP:
                BasicMapAPIExample.SomeOtherFunction ();
                break;
            case BasicMapController.CLIENT_KEY:
                BasicMapAPIExample.SomeThirdFunction ();
                break;
            default:
                break;
        }
        super.OnGroupChanged (group);
    }
}