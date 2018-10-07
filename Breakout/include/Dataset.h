#ifndef DATASET_H
#define DATASET_H

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "SDL.h"
#include "tinyxml2.h"

#include "Button.h"
#include "Constants.h"
#include "ImageObject.h"
#include "Label.h"
#include "UIObject.h"

class Dataset
{
public:
	Dataset();
	~Dataset();
	void destroy();
	bool parseLayout(const char* filename);

private:
	void extractButtonAttributes(tinyxml2::XMLNode* root);
	void extractLabelAttributes(tinyxml2::XMLNode* root);
	void extractImageAttributes(tinyxml2::XMLNode* root);
	bool checkXmlResult(tinyxml2::XMLError error);
	std::vector<std::string> splitString(const char* input);

public:
	std::map<std::string, Label*> getLabels() const;
	std::map<std::string, Button*> getButtons() const;
	std::map<std::string, ImageObject*> getImages() const;

private:
	std::map<std::string, Label*> labels;
	std::map<std::string, Button*> buttons;
	std::map<std::string, ImageObject*> images;
};

#endif // !DATASET_H
