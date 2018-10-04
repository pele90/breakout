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
#include "ImageObject.h"
#include "Button.h"

class Dataset
{
public:
	Dataset();
	~Dataset();
	void destroy();

	bool parseLayout(const char* filename);
	void extractButtonAttributes(tinyxml2::XMLNode* root);
	void extractLabelAttributes(tinyxml2::XMLNode* root);
	void extractImageAttributes(tinyxml2::XMLNode* root);
	bool checkXmlResult(tinyxml2::XMLError error);
	std::vector<std::string> splitString(const char* input);

	std::vector<Button*> getButtons() const;
	std::vector<Label*> getLabels() const;
	std::vector<ImageObject*> getImages() const;

private:
	std::vector<Label*> labels;
	std::vector<Button*> buttons;
	std::vector<ImageObject*> images;
};

#endif // !DATASET_H
