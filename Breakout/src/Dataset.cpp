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
		Util::showMessageBox("Error creating ROOT NODE!");
		return false;
	}

	//---------------LABEL-----------------------------
	extractLabelAttributes(pRoot);

	//---------------BUTTON-----------------------------
	extractButtonAttributes(pRoot);

	//---------------IMAGE-----------------------------
	extractImageAttributes(pRoot);

	return true;
}

void Dataset::extractButtonAttributes(tinyxml2::XMLNode* root)
{
	tinyxml2::XMLElement* pElement = root->FirstChildElement(BUTTON_ELEMENT);
	bool visible;

	while (pElement != nullptr)
	{
		Button* button = new Button();

		tinyxml2::XMLError eResult;

		button->setName(pElement->Attribute(NAME_ATTRIBUTE));

		const char* value = pElement->Attribute(VISIBLE_ATTRIBUTE);
		if (value == NULL)
		{
			visible = true;
		}
		else
		{
			visible = std::strcmp(value, VISIBLE_FALSE_VALUE) == 0 ? false : true;
		}
		button->setVisibility(visible);

		const char* texture_name;
		eResult = pElement->QueryStringAttribute(TEXTURE_NAME_ATTRIBUTE, &texture_name);
		if (!checkXmlResult(eResult))
		{
			texture_name = "";
		}
		button->setTextureFilename(texture_name);

		const char* rect;
		eResult = pElement->QueryStringAttribute(RECT_ATTRIBUTE, &rect);
		if (!checkXmlResult(eResult))
		{
			rect = NULL;
		}

		std::vector<std::string> tokens = this->splitString(rect);
		SDL_Rect transform = { stoi(tokens[0]), stoi(tokens[1]), stoi(tokens[2]), stoi(tokens[3]) };
		button->setTransform(transform);

		buttons[button->getName()] = button;

		pElement = pElement->NextSiblingElement(BUTTON_ELEMENT);
	}
}

void Dataset::extractLabelAttributes(tinyxml2::XMLNode* root)
{
	tinyxml2::XMLElement* pElement = root->FirstChildElement(LABEL_ELEMENT);
	bool visible;

	while (pElement != nullptr)
	{
		Label* label = new Label();

		label->setName(pElement->Attribute(NAME_ATTRIBUTE));

		const char* value = pElement->Attribute(VISIBLE_ATTRIBUTE) == NULL ? VISIBLE_TRUE_VALUE : pElement->Attribute(VISIBLE_ATTRIBUTE);
		visible = std::strcmp(value, VISIBLE_FALSE_VALUE) == 0 ? false : true;
		label->setVisibility(visible);

		label->setText(pElement->Attribute(TEXT_ATTRIBUTE));
		label->setFontName(pElement->Attribute(FONT_NAME));

		std::string fontColor = pElement->Attribute(FONT_COLOR);
		std::vector<std::string> fontColorTokens = splitString(fontColor.c_str());
		SDL_Color fColor = { std::stoi(fontColorTokens[0]), std::stoi(fontColorTokens[1]), std::stoi(fontColorTokens[2]), std::stoi(fontColorTokens[3]) };
		label->setFontColor(fColor);

		int fontSize;
		pElement->QueryIntAttribute(FONT_SIZE, &fontSize);
		label->setFontSize(fontSize);

		const char* rect;
		pElement->QueryStringAttribute(RECT_ATTRIBUTE, &rect);
		std::vector<std::string> rectTokens = splitString(rect);
		SDL_Rect transform = { std::stoi(rectTokens[0]), std::stoi(rectTokens[1]), std::stoi(rectTokens[2]), std::stoi(rectTokens[3]) };
		label->setTransform(transform);

		labels[label->getName()] = label;

		pElement = pElement->NextSiblingElement(LABEL_ELEMENT);
	}
}

void Dataset::extractImageAttributes(tinyxml2::XMLNode* root)
{
	tinyxml2::XMLElement* pElement = root->FirstChildElement(IMAGE_ELEMENT);
	bool visible;

	while (pElement != nullptr)
	{
		ImageObject* imageObject = new ImageObject();

		imageObject->setName(pElement->Attribute(NAME_ATTRIBUTE));

		const char* value = pElement->Attribute(VISIBLE_ATTRIBUTE) == NULL ? VISIBLE_TRUE_VALUE : VISIBLE_FALSE_VALUE;
		visible = std::strcmp(value, VISIBLE_FALSE_VALUE) == 0 ? false : true;
		imageObject->setVisibility(visible);

		imageObject->setTextureFilename(pElement->Attribute(TEXTURE_NAME_ATTRIBUTE));

		const char* rect;
		pElement->QueryStringAttribute(RECT_ATTRIBUTE, &rect);
		std::vector<std::string> tokens = splitString(rect);
		SDL_Rect transform = { std::stoi(tokens[0]), std::stoi(tokens[1]), std::stoi(tokens[2]), std::stoi(tokens[3]) };
		imageObject->setTransform(transform);

		images[imageObject->getName()] = imageObject;

		pElement = pElement->NextSiblingElement(IMAGE_ELEMENT);
	}
}

bool Dataset::checkXmlResult(tinyxml2::XMLError error)
{
	if (error != tinyxml2::XML_SUCCESS)
	{
		Util::showMessageBox("Error parsing XML file! Error: " + error);
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

std::map<std::string, Label*> Dataset::getLabels() const
{
	return this->labels;
}

std::map<std::string, Button*> Dataset::getButtons() const
{
	return this->buttons;
}

std::map<std::string, ImageObject*> Dataset::getImages() const
{
	return this->images;
}