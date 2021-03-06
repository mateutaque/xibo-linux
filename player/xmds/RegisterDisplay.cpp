#include "RegisterDisplay.hpp"

#include "Resources.hpp"
#include "utils/Utilities.hpp"

namespace Resources = XMDSResources::RegisterDisplay;

SOAP::RequestSerializer<RegisterDisplay::Request>::RequestSerializer(const RegisterDisplay::Request& request) : BaseRequestSerializer(request)
{
}

std::string SOAP::RequestSerializer<RegisterDisplay::Request>::string()
{
    return createRequest(Resources::Name, request().clientCode, request().clientType, request().clientVersion,
                         request().displayName, request().macAddress, request().serverKey, request().hardwareKey);

}

SOAP::ResponseParser<RegisterDisplay::Result>::ResponseParser(const std::string& soapResponse) : BaseResponseParser(soapResponse)
{
}

RegisterDisplay::Result SOAP::ResponseParser<RegisterDisplay::Result>::doParse(const boost::property_tree::ptree& node)
{
    auto activationMessage = node.get<std::string>(Resources::ActivationMessage);
    auto display = Utils::parseXmlFromString(activationMessage).get_child(Resources::Display);
    auto attrs = display.get_child(Resources::DisplayAttrs);

    RegisterDisplay::Result result;
    result.status.code = static_cast<RegisterDisplay::Result::Status::Code>(attrs.get<int>(Resources::Status));
    result.status.message = attrs.get<std::string>(Resources::StatusMessage);
    if(result.status.code == RegisterDisplay::Result::Status::Code::Ready)
    {
        fillPlayerSettings(result.playerSettings, display);
    }

    return result;
}

void SOAP::ResponseParser<RegisterDisplay::Result>::fillPlayerSettings(PlayerSettings& settings, const boost::property_tree::ptree& display)
{
    namespace Settings = Resources::Settings;

    settings.collectInterval = display.get<int>(Settings::CollectInterval);
    settings.downloadStartWindow = display.get<std::string>(Settings::DownloadStartWindow);
    settings.downloadEndWindow = display.get<std::string>(Settings::DownloadEndWindow);
    settings.statsEnabled = display.get<bool>(Settings::StatsEnabled);
    settings.xmrNetworkAddress = display.get<std::string>(Settings::XmrNetworkAddress);
    settings.sizeX = display.get<double>(Settings::SizeX);
    settings.sizeY = display.get<double>(Settings::SizeY);
    settings.offsetX = display.get<double>(Settings::OffsetX);
    settings.offsetY = display.get<double>(Settings::OffsetY);
    settings.logLevel = toLogLevelEnum(display.get<std::string>(Settings::LogLevel));
    settings.shellCommandsEnabled = display.get<bool>(Settings::EnableShellCommands);
    settings.modifiedLayoutsEnabled = display.get<bool>(Settings::ExpireModifiedLayouts);
    settings.maxConcurrentDownloads = display.get<int>(Settings::MaxConcurrentDownloads);
    //shellCommandAllowList
    settings.statusLayoutUpdate = display.get<bool>(Settings::SendCurrentLayoutAsStatusUpdate);
    settings.screenshotInterval = display.get<int>(Settings::ScreenShotRequestInterval);
    settings.screenshotSize = display.get<int>(Settings::ScreenShotSize);
    settings.maxLogFilesUploads = display.get<int>(Settings::MaxLogFileUploads);
    settings.embeddedServerPort = display.get<int>(Settings::EmbeddedServerPort);
    settings.preventSleep = display.get<bool>(Settings::PreventSleep);
    settings.displayName = display.get<std::string>(Settings::DisplayName);
    settings.screenshotRequested = display.get<bool>(Settings::ScreenShotRequested);
}


spdlog::level::level_enum SOAP::ResponseParser<RegisterDisplay::Result>::toLogLevelEnum(const std::string& level)
{
    if(level == "audit")
        return spdlog::level::level_enum::trace;
    else if(level == "info")
        return spdlog::level::level_enum::debug;
    else if(level == "error")
        return spdlog::level::level_enum::warn;
    else
        return spdlog::level::level_enum::off;
}
