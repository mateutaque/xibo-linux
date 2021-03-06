#pragma once

#include "utils/IFileSystemAdaptor.hpp"
#include <gmock/gmock.h>

class MockFileSystemAdaptor : public IFileSystemAdaptor
{
public:
    MOCK_CONST_METHOD1(isRegularFile, bool(const FilePath& path));

};
