/*
 * Your License or Copyright can go here
 */

#include "ProgWorkshopPlugin.h"

#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QTextStream>

#include "SIMPLib/Filtering/FilterFactory.hpp"
#include "SIMPLib/Filtering/FilterManager.h"

#include "ProgWorkshop/ProgWorkshopConstants.h"
#include "ProgWorkshop/ProgWorkshopVersion.h"
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
ProgWorkshopPlugin::ProgWorkshopPlugin()
: m_Version(ProgWorkshop::Version::Complete())
, m_CompatibilityVersion(ProgWorkshop::Version::Package())
, m_Vendor("Open-Source")
, // Initialize ProgWorkshop's Vendor Name Here
m_URL("http://www.github.com/bluequartzsoftware/ProgWorkshop")
, // Initialize Company URL Here
m_Location("")
, // Initialize ProgWorkshop library Location Here
m_Description("Descrption")
, // Initialize ProgWorkshop's Description Here
m_Copyright("")
, // Initialize ProgWorkshop's Copyright Here
m_Filters(QList<QString>())
, // Initialize ProgWorkshop's List of Dependencies Here
m_DidLoad(false)
{
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
ProgWorkshopPlugin::~ProgWorkshopPlugin() = default;

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString ProgWorkshopPlugin::getPluginFileName()
{
  return ProgWorkshopConstants::ProgWorkshopPluginFile;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString ProgWorkshopPlugin::getPluginDisplayName()
{
  return ProgWorkshopConstants::ProgWorkshopPluginDisplayName;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString ProgWorkshopPlugin::getPluginBaseName()
{
  return ProgWorkshopConstants::ProgWorkshopBaseName;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString ProgWorkshopPlugin::getVersion()
{
  return m_Version;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString ProgWorkshopPlugin::getCompatibilityVersion()
{
  return m_CompatibilityVersion;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString ProgWorkshopPlugin::getVendor()
{
  return m_Vendor;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString ProgWorkshopPlugin::getURL()
{
  return m_URL;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString ProgWorkshopPlugin::getLocation()
{
  return m_Location;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString ProgWorkshopPlugin::getDescription()
{
  /* PLEASE UPDATE YOUR PLUGIN'S DESCRIPTION FILE.
  It is located at ProgWorkshop/Resources/ProgWorkshop/ProgWorkshopDescription.txt */

  QFile licenseFile(":/ProgWorkshop/ProgWorkshopDescription.txt");
  QFileInfo licenseFileInfo(licenseFile);
  QString text = "<<--Description was not read-->>";

  if(licenseFileInfo.exists())
  {
    if(licenseFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      QTextStream in(&licenseFile);
      text = in.readAll();
    }
  }
  return text;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString ProgWorkshopPlugin::getCopyright()
{
  return m_Copyright;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString ProgWorkshopPlugin::getLicense()
{
  /* PLEASE UPDATE YOUR PLUGIN'S LICENSE FILE.
  It is located at ProgWorkshop/Resources/ProgWorkshop/ProgWorkshopLicense.txt */

  QFile licenseFile(":/ProgWorkshop/ProgWorkshopLicense.txt");
  QFileInfo licenseFileInfo(licenseFile);
  QString text = "<<--License was not read-->>";

  if(licenseFileInfo.exists())
  {
    if(licenseFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      QTextStream in(&licenseFile);
      text = in.readAll();
    }
  }
  return text;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QMap<QString, QString> ProgWorkshopPlugin::getThirdPartyLicenses()
{
  QMap<QString, QString> licenseMap;
  QList<QString> fileStrList;
  fileStrList.push_back(":/ThirdParty/HDF5.txt");

  fileStrList.push_back(":/ThirdParty/Qt.txt");
  fileStrList.push_back(":/ThirdParty/Qwt.txt");

  for(const auto& filepath : fileStrList)
  {
    QFile file(filepath);
    QFileInfo licenseFileInfo(file);

    if(licenseFileInfo.exists())
    {
      if(file.open(QIODevice::ReadOnly | QIODevice::Text))
      {
        QTextStream in(&file);
        licenseMap.insert(licenseFileInfo.baseName(), in.readAll());
      }
    }
  }

  return licenseMap;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool ProgWorkshopPlugin::getDidLoad()
{
  return m_DidLoad;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ProgWorkshopPlugin::setDidLoad(bool didLoad)
{
  m_DidLoad = didLoad;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ProgWorkshopPlugin::setLocation(QString filePath)
{
  m_Location = filePath;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ProgWorkshopPlugin::writeSettings(QSettings& prefs)
{
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ProgWorkshopPlugin::readSettings(QSettings& prefs)
{
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ProgWorkshopPlugin::registerFilterWidgets(FilterWidgetManager* fwm)
{
}

#include "ProgWorkshopFilters/RegisterKnownFilters.cpp"
