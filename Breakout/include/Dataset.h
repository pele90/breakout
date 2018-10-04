#ifndef DATASET_H
#define DATASET_H

#include <string>
#include <iostream>
#include <sstream>
#include <vector>

#include "SDL.h"
#include "tinyxml2.h"

#include "Resources.h"
#include "UIObject.h"
#include "Label.h"
#include "Image.h"
#include "Button.h"

class Dataset
{
public:
	Dataset();
	~Dataset();

	bool parseLayout(const char* filename);
	void extractAttributes(tinyxml2::XMLElement* element, UIObject* object);
	bool checkXmlResult(tinyxml2::XMLError error);
	std::vector<std::string> splitString(const char* input);

	std::vector<Button*> getButtons() const;
	std::vector<Label*> getLabels() const;
	//std::vector<Image*> getImages() const;

private:
	std::vector<Label*> labels;
	std::vector<Button*> buttons;
	//std::vector<Image*> images;
};

#endif // !DATASET_H
