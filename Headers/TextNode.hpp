#pragma once

#include <SceneNode.hpp>
#include <ResourceIdentifier.hpp>
#include <ResourceHolder.hpp>

#include <SFML\Graphics\Text.hpp>
#include <SFML\Graphics\RenderTarget.hpp>
#include <SFML\Graphics\RenderStates.hpp>

#include <string>

class TextNode : public SceneNode
{
public:
  explicit  TextNode::TextNode(const FontHolder& font, const std::string& text);

            void      setString(const std::string& text);

private:
 virtual    void      drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
  sf::Text            mText;
};