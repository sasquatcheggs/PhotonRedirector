#include "photon_redirect.h"

PhotonRedirector::PhotonRedirector() {
    LoadConfig();
}

std::string PhotonRedirector::Redirect(const std::string& domain) {
    auto it = m_redirects.find(domain);
    if (it != m_redirects.end()) {
        return it->second;
    }

    // Default redirect for Photon domains
    const char* photon_domains[] = {
        "ns.exitgames.io", "ns.exitgames.com",
        "ns.photonengine.io", "ns.photonengine.com"
    };

    for (const char* d : photon_domains) {
        if (domain == d) {
            return "127.0.0.1";
        }
    }

    return "";
}

void PhotonRedirector::LoadConfig() {
    m_redirects.clear();

    std::ifstream file("LANSettings.txt");
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line)) {
        size_t comment = line.find('#');
        if (comment != std::string::npos) line = line.substr(0, comment);

        // Trim whitespace
        size_t start = line.find_first_not_of(" \t\r\n");
        if (start == std::string::npos) continue;
        size_t end = line.find_last_not_of(" \t\r\n");
        line = line.substr(start, end - start + 1);

        size_t delim = line.find('|');
        if (delim != std::string::npos) {
            std::string domain = line.substr(0, delim);
            std::string ip = line.substr(delim + 1);

            // Trim again
            domain.erase(0, domain.find_first_not_of(" \t"));
            domain.erase(domain.find_last_not_of(" \t") + 1);
            ip.erase(0, ip.find_first_not_of(" \t"));
            ip.erase(ip.find_last_not_of(" \t") + 1);

            // Remove port if present
            size_t port_delim = ip.find(':');
            if (port_delim != std::string::npos) {
                ip = ip.substr(0, port_delim);
            }

            m_redirects[domain] = ip;

            char msg[256];
            sprintf_s(msg, "Loaded redirect: %s -> %s", domain.c_str(), ip.c_str());
            OutputDebugStringA(msg);
        }
    }
    file.close();
}

PhotonRedirector g_Redirector;