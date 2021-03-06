#include "BackgroundBuilderTests.hpp"
#include "control/Background.hpp"

using namespace testing;

TEST(BackgroundBuilderTest, ConstructWithColor_Default_HandlerSetSizeShouldBeCalled)
{
    auto adaptor = std::make_unique<NiceMock<MockImageAdaptor>>();

    EXPECT_CALL(*adaptor, setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT));

    BackgroundBuilderTest().defaultSize().adaptor(std::move(adaptor)).color(DEFAULT_COLOR).build();
}

TEST(BackgroundBuilderTest, ConstructWithPath_Default_HandlerLoadImageWithPreserveAspectRatioShouldBeCalled)
{
    BackgroundBuilderTest builder;
    auto adaptor = std::make_unique<NiceMock<MockImageAdaptor>>();

    EXPECT_CALL(*adaptor, loadImage(DEFAULT_FULL_PATH, true));

    builder.defaultSize().adaptor(std::move(adaptor)).path(DEFAULT_PATH.string()).build();
}

TEST(BackgroundBuilderTest, Construct_WithoutPathAndColor_ShouldThrowRunTimeError)
{
    ASSERT_THROW(BackgroundBuilderTest().defaultSize().build(), std::runtime_error);
}

TEST_P(BackgroundBuilderSizeTest, Construct_InvalidSize_ShouldThrowInvalidArgError)
{
    ASSERT_THROW(BackgroundBuilderTest().width(GetParam().width).height(GetParam().height).build(), std::invalid_argument);
}

INSTANTIATE_TEST_CASE_P(Suite, BackgroundBuilderSizeTest, ::testing::ValuesIn(invalidBackgroundSizes));

TEST_P(BackgroundBuilderValidColorTest, Construct_ValidColor_HandlerSetColorWithConvertedStringShouldBeCalled)
{
    auto adaptor = std::make_unique<NiceMock<MockImageAdaptor>>();

    EXPECT_CALL(*adaptor, setColor(GetParam().numberColor));

    BackgroundBuilderTest().defaultSize().adaptor(std::move(adaptor)).color(GetParam().strColor).build();
}

INSTANTIATE_TEST_CASE_P(Suite, BackgroundBuilderValidColorTest, ::testing::ValuesIn(validColors));

TEST_P(BackgroundBuilderInvalidColorTest, Construct_InvalidColor_InvalidArgumentShouldBeThrown)
{
    ASSERT_THROW(BackgroundBuilderTest().defaultSize().color(GetParam()).build(), std::invalid_argument);
}

INSTANTIATE_TEST_CASE_P(Suite, BackgroundBuilderInvalidColorTest, ::testing::ValuesIn(invalidColors));

TEST(BackgroundBuilderTest, Construct_DefaultColorPath_ColorShouldNotBeSetPathShouldBeSet)
{
    BackgroundBuilderTest builder;

    auto background = builder.defaultSize().color(DEFAULT_COLOR).path(DEFAULT_PATH.string()).build();
    EXPECT_TRUE(dynamic_cast<ImageBackground*>(background.get()));
}

TEST(BackgroundBuilderTest, Construct_InvalidPath_ShouldThrowRunTimeError)
{
    BackgroundBuilderTest builder;

    ON_CALL(builder.filesystem(), isRegularFile(_)).WillByDefault(Return(false));

    ASSERT_THROW(builder.defaultSize().path(DEFAULT_PATH.string()).build(), std::runtime_error);
}

