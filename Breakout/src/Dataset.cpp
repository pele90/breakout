#include "Dataset.h"

Dataset::Dataset()
{
}

Dataset::~Dataset()
{
}


bool Dataset::parseLayout(const char* filename)
{
	std::string xmlFilename = DEFAULT_LAYOUT_PATH;
	xmlFilename.append(filename).append(".xml");
	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLError eResult = xmlDoc.LoadFile(xmlFilename.c_str());
	if (!checkXmlResult(eResult))
	{
		return false;
	}

	tinyxml2::XMLNode * pRoot = xmlDoc.FirstChild();
	if (pRoot == nullptr)
	{
		std::cout << "Error creating ROOT NODE!" << std::endl;
		return false;
	}

	//---------------BUTTON-----------------------------
	tinyxml2::XMLElement* pElement = pRoot->FirstChildElement("Button");
	while (pElement != nullptr)
	{
		Button* button = new Button();

		tinyxml2::XMLError eResult;

		const char* texture_name;
		eResult = pElement->QueryStringAttribute("texture_name", &texture_name);
		if (!checkXmlResult(eResult))
		{
			texture_name = "";
		}
		button->setTextureFilename(texture_name);

		const char* rect;
		eResult = pElement->QueryStringAttribute("rect", &rect);
		if (!checkXmlResult(eResult))
		{
			rect = NULL;
		}

		std::vector<std::string> tokens = this->splitString(rect);
		SDL_Rect transform = { stoi(tokens[0]), stoi(tokens[1]), stoi(tokens[2]), stoi(tokens[3]) };
		button->setTransform(transform);

		buttons.push_back(button);

		pElement = pElement->NextSiblingElement("Button");
	}

	//---------------LABEL-----------------------------
	pElement = pRoot->FirstChildElement("Label");
	while (pElement != nullptr)
	{
		Label* label = new Label();

		tinyxml2::XMLError eResult;

		const char* text;
		eResult = pElement->QueryStringAttribute("text", &text);
		if (!checkXmlResult(eResult))
		{
			text = NULL;
		}
		label->setText(text);

		const char* fontName;
		eResult = pElement->QueryStringAttribute("font_name", &fontName);
		if (!checkXmlResult(eResult))
		{
			fontName = NULL;
		}
		label->setFontName(fontName);

		const char* fontColor;
		eResult = pElement->QueryStringAttribute("font_color", &fontColor);
		if (!checkXmlResult(eResult))
		{
			fontColor = NULL;
		}
		std::vector<std::string> fontColorTokens = splitString(fontColor);
		SDL_Color fColor = { std::stoi(fontColorTokens[0]), std::stoi(fontColorTokens[1]), std::stoi(fontColorTokens[2]), std::stoi(fontColorTokens[3]) };
		label->setFontColor(fColor);

		int fontSize;
		eResult = pElement->QueryIntAttribute("font_size", &fontSize);
		if (!checkXmlResult(eResult))
		{
			text = NULL;
		}
		label->setFontSize(fontSize);


		const char* rect;
		eResult = pElement->QueryStringAttribute("rect", &rect);
		if (!checkXmlResult(eResult))
		{
			rect = NULL;
		}

		std::vector<std::string> rectTokens = splitString(rect);
		SDL_Rect transform = { std::stoi(rectTokens[0]), std::stoi(rectTokens[1]), std::stoi(rectTokens[2]), std::stoi(rectTokens[3]) };
		label->setTransform(transform);

		labels.push_back(label);

		pElement = pElement->NextSiblingElement("Label");
	}

	return true;
}

void Dataset::extractAttributes(tinyxml2::XMLElement* element, UIObject* object)
{
	
}

bool Dataset::checkXmlResult(tinyxml2::XMLError error)
{
	if (error != tinyxml2::XML_SUCCESS)
	{
		std::cout << "Error: " << error << std::endl;
		return false;
	}

	return true;
}

std::vector<std::string> Dataset::splitString(const char* input)
{
	std::vector<std::string> result;

	do
	{
		const char *begin = input;

		while (*input != ',' && *input)
			input++;

		result.push_back(std::string(begin, input));
	} while (0 != *input++);

	return result;
}

std::vector<Button*> Dataset::getButtons() const
{
	return this->buttons;
}

std::vector<Label*> Dataset::getLabels() const
{
	return this->labels;
}