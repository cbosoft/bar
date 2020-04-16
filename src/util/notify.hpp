#pragma once
#include <string>

void notify(std::string title, std::string body="", std::string urgency="normal", int timeout_s=-1);
