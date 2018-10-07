#include "Dataset.h"

Dataset::Dataset()
{
}

Dataset::~Dataset()
{
}

void Dataset::destroy()
{
	for (auto it : buttons)
	{
		it.second->destroy();
		delete it.second;
	}

	for (auto it : labels)
	{
		it.second->destroy();
		delete it.second;
	}

	for (auto it : images)
	{
		it.second->destroy();
		delete it.second;
	}

	buttons.clear();
	labels.clear();
	images.clear();
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

	tinyxml2::XMLNode* pRoot = xmlDoc.FirstChild();
	if (pRoot == nullptr)
	{
		std::cout << "Error creating ROOT NODE!" << std::endl;
		return false;
	}

	//---------------BUTTON-----------------------------
	extractButtonAttributes(pRoot);

	//---------------LABEL-----------------------------
	extractLabelAttributes(pRoot);

	//---------------IMAGE-----------------------------
	extractImageAttributes(pRoot);

	return true;
}

void Dataset::extractButtonAttributes(tinyxml2::XMLNode* root)
{
	tinyxml2::XMLElement* pElement = root->FirstChildElement("Button");
	bool visible;

	while (pElement != nullptr)
	{
		Button* button = new Button();

		tinyxml2::XMLError eResult;

		button->setName(pElement->Attribute("name"));

		const char* value = pElement->Attribute("visible");
		if (value == NULL)
		{
			visible = true;
		}
		else
		{
			visible = std::strcmp(value, "0") == 0 ? false : true;
		}
		button->setVisibility(visible);

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

		buttons[button->getName()] = button;

		pElement = pElement->NextSiblingElement("Button");
	}
}

void Dataset::extractLabelAttributes(tinyxml2::XMLNode* root)
{
	tinyxml2::XMLElement* pElement = root->FirstChildElement("Label");
	bool visible;

	while (pElement != nullptr)
	{
		Label* label = new Label();

		tinyxml2::XMLError eResult;

		label->setName(pElement->Attribute("name"));

		const char* value = pElement->Attribute("visible") == NULL ? "1" : "0";
		visible = std::strcmp(value, "0") == 0 ? false : true;
		label->setVisibility(visible);

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

		labels[label->getName()] = label;

		pElement = pElement->NextSiblingElement("Label");
	}
}

void Dataset::extractImageAttributes(tinyxml2::XMLNode* root)
{
	tinyxml2::XMLElement* pElement = root->FirstChildElement("Image");
	bool visible;

	while (pElement != nullptr)
	{
		ImageObject* imageObject = new ImageObject();

		tinyxml2::XMLError eResult;

		imageObject->setName(pElement->Attribute("name"));

		const char* value = pElement->Attribute("visible") == NULL ? "1" : "0";
		visible = std::strcmp(value, "0") == 0 ? false : true;
		imageObject->setVisibility(visible);

		const char* texture_name;
		eResult = pElement->QueryStringAttribute("texture_name", &texture_name);
		if (!checkXmlResult(eResult))
		{
			texture_name = nullptr;
		}
		imageObject->setTextureFilename(texture_name);

		const char* rect;
		eResult = pElement->QueryStringAttribute("rect", &rect);
		if (!checkXmlResult(eResult))
		{
			rect = nullptr;
		}

		std::vector<std::string> tokens = splitString(rect);
		SDL_Rect transform = { std::stoi(tokens[0]), std::stoi(tokens[1]), std::stoi(tokens[2]), std::stoi(tokens[3]) };
		imageObject->setTransform(transform);

		images[imageObject->getName()] = imageObject;

		pElement = pElement->NextSiblingElement("Image");
	}
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

std::map<std::string, Button*> Dataset::getButtons() const
{
	return this->buttons;
}

std::map<std::string, Label*> Dataset::getLabels() const
{
	return this->labels;
}

std::map<std::string, ImageObject*> Dataset::getImages() const
{
	return this->images;
}