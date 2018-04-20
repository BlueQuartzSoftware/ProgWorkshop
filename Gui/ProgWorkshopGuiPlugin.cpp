

#include "ProgWorkshopGuiPlugin.h"

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
ProgWorkshopGuiPlugin::ProgWorkshopGuiPlugin()
: ProgWorkshopPlugin()
{
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
ProgWorkshopGuiPlugin::~ProgWorkshopGuiPlugin() = default;

#include "ProgWorkshop/Gui/FilterParameterWidgets/RegisterKnownFilterParameterWidgets.cpp"
