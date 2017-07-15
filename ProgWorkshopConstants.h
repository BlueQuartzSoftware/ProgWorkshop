/*
 * Your License should go here
 */
#ifndef _progworkshopconstants_h_
#define _progworkshopconstants_h_

#include <QtCore/QString>

/**
* @brief This namespace is used to define some Constants for the plugin itself.
*/
namespace ProgWorkshopConstants
{
  const QString ProgWorkshopPluginFile("ProgWorkshopPlugin");
  const QString ProgWorkshopPluginDisplayName("ProgWorkshopPlugin");
  const QString ProgWorkshopBaseName("ProgWorkshopPlugin");

  namespace FilterGroups
  {
  	const QString ProgWorkshopFilters("ProgWorkshop");
  }
}

/**
* @brief Use this namespace to define any custom GUI widgets that collect FilterParameters
* for a filter. Do NOT define general reusable widgets here.
*/
namespace FilterParameterWidgetType
{
/* const QString SomeCustomWidget("SomeCustomWidget"); */
}
#endif
