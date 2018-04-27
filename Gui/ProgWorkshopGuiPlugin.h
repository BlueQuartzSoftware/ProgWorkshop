#pragma once

#include "ProgWorkshop/ProgWorkshopPlugin.h"

class ProgWorkshopGuiPlugin : public ProgWorkshopPlugin
{
  Q_OBJECT
  Q_INTERFACES(ISIMPLibPlugin)
  Q_PLUGIN_METADATA(IID "net.bluequartz.dream3d.ProgWorkshopGuiPlugin")

public:
  ProgWorkshopGuiPlugin();
   ~ProgWorkshopGuiPlugin() override;
  
  /**
   * @brief Register all the filters with the FilterWidgetFactory
   */
  void registerFilterWidgets(FilterWidgetManager* fwm) override;
  

public:
  ProgWorkshopGuiPlugin(const ProgWorkshopGuiPlugin&) = delete;            // Copy Constructor Not Implemented
  ProgWorkshopGuiPlugin(ProgWorkshopGuiPlugin&&) = delete;                 // Move Constructor
  ProgWorkshopGuiPlugin& operator=(const ProgWorkshopGuiPlugin&) = delete; // Copy Assignment Not Implemented
  ProgWorkshopGuiPlugin& operator=(ProgWorkshopGuiPlugin&&) = delete;      // Move Assignment Not Implemented
};
