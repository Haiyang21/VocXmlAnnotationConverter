/* ==========================================================================
function :		annotate

Author :		frisch zenger

Date :			2015-03-29

Purpose :		"to Annotate the Images by VOC format xmls".
========================================================================*/

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "tinyxml.h"

using namespace std;

typedef struct _coords
{
	string name;
	string pose;
	string truncated;
	string difficult;
	int xmin;
	int ymin;
	int xmax;
	int ymax;
}coords;

typedef struct _image_object
{
	string file_name;
	string folder_name;
	string database_name;
	string annotation;
	string image_source;
	string image_id;
	string flickr_id;
	string flickr_name;
	string segmented;
	int size_width;
	int size_height;
	int size_depth;

	vector<coords> bboxes;

}IMAGE_OBJECT;

void annotate(IMAGE_OBJECT obj)
{
	stringstream ss;
	string filename = "", tempStr;
	//create a XML document object
	TiXmlDocument *myDocument = new TiXmlDocument();
	//create a root node and link to it
	{
		TiXmlElement *RootElement = new TiXmlElement("annotation");
		myDocument->LinkEndChild(RootElement);

		{
			//create a folder element and link to it。
			TiXmlElement *folderElement = new TiXmlElement("folder");
			RootElement->LinkEndChild(folderElement);
			TiXmlText *FolderContent = new TiXmlText(obj.folder_name.c_str());
			folderElement->LinkEndChild(FolderContent);

			//create a filename element
			TiXmlElement *filenameElement = new TiXmlElement("filename");
			RootElement->LinkEndChild(filenameElement);
			TiXmlText *filenameContent = new TiXmlText(obj.file_name.c_str());
			filenameElement->LinkEndChild(filenameContent);


			TiXmlElement *sourceElement = new TiXmlElement("source");
			RootElement->LinkEndChild(sourceElement);

			{
				TiXmlElement *databaseElement = new TiXmlElement("database");
				sourceElement->LinkEndChild(databaseElement);
				TiXmlText *databaseContent = new TiXmlText(obj.database_name.c_str());
				databaseElement->LinkEndChild(databaseContent);
				//-------------------
				TiXmlElement *annotationElement = new TiXmlElement("annotation");
				sourceElement->LinkEndChild(annotationElement);
				TiXmlText *annotationContent = new TiXmlText(obj.annotation.c_str());
				annotationElement->LinkEndChild(annotationContent);
				//-------------------
				TiXmlElement *imageElement = new TiXmlElement("image");
				sourceElement->LinkEndChild(imageElement);
				TiXmlText *imageContent = new TiXmlText(obj.image_source.c_str());
				imageElement->LinkEndChild(imageContent);
				//-------------------
				TiXmlElement *flickridElement = new TiXmlElement("flickrid");
				sourceElement->LinkEndChild(flickridElement);
				TiXmlText *flickridContent = new TiXmlText(obj.image_id.c_str());
				flickridElement->LinkEndChild(flickridContent);
			}

			TiXmlElement *ownerElement = new TiXmlElement("owner");
			RootElement->LinkEndChild(ownerElement);
			{
				TiXmlElement *flickridElement = new TiXmlElement("flickrid");
				ownerElement->LinkEndChild(flickridElement);
				TiXmlText *flickridContent = new TiXmlText(obj.flickr_id.c_str());
				flickridElement->LinkEndChild(flickridContent);
				//--------------------
				TiXmlElement *nameElement = new TiXmlElement("name");
				ownerElement->LinkEndChild(nameElement);
				TiXmlText *nameContent = new TiXmlText(obj.flickr_name.c_str());
				nameElement->LinkEndChild(nameContent);
			}

			TiXmlElement *sizeElement = new TiXmlElement("size");
			RootElement->LinkEndChild(sizeElement);
			{
				TiXmlElement *widthElement = new TiXmlElement("width");
				sizeElement->LinkEndChild(widthElement);
				TiXmlText *widthContent = new TiXmlText(std::to_string(obj.size_width).c_str());
				widthElement->LinkEndChild(widthContent);
				//--------------------
				TiXmlElement *heightElement = new TiXmlElement("height");
				sizeElement->LinkEndChild(heightElement);
				TiXmlText *heightContent = new TiXmlText(std::to_string(obj.size_height).c_str());
				heightElement->LinkEndChild(heightContent);
				//--------------------
				TiXmlElement *depthElement = new TiXmlElement("depth");
				sizeElement->LinkEndChild(depthElement);
				TiXmlText *depthContent = new TiXmlText(std::to_string(obj.size_depth).c_str());
				depthElement->LinkEndChild(depthContent);
			}

			//create a filename element
			TiXmlElement *segmentedElement = new TiXmlElement("segmented");
			RootElement->LinkEndChild(segmentedElement);
			TiXmlText *segmentedContent = new TiXmlText(obj.segmented.c_str());
			segmentedElement->LinkEndChild(segmentedContent);
			for (size_t i = 0; i < obj.bboxes.size(); i++)
			{
				TiXmlElement *objects = new TiXmlElement("object");
				RootElement->LinkEndChild(objects);
				{
					TiXmlElement *name = new TiXmlElement("name");
					objects->LinkEndChild(name);
					TiXmlText *nameContent = new TiXmlText(obj.bboxes[i].name.c_str());
					name->LinkEndChild(nameContent);
					//--------------------
					TiXmlElement *pose = new TiXmlElement("pose");
					objects->LinkEndChild(pose);
					TiXmlText *poseContent = new TiXmlText(obj.bboxes[i].pose.c_str());
					pose->LinkEndChild(poseContent);
					//--------------------
					TiXmlElement *truncated = new TiXmlElement("truncated");
					objects->LinkEndChild(truncated);
					TiXmlText *truncatedContent = new TiXmlText(obj.bboxes[i].truncated.c_str());
					truncated->LinkEndChild(truncatedContent);
					//--------------------
					TiXmlElement *difficult = new TiXmlElement("difficult");
					objects->LinkEndChild(difficult);
					TiXmlText *difficultContent = new TiXmlText(obj.bboxes[i].difficult.c_str());
					difficult->LinkEndChild(difficultContent);
					//--------------------
					TiXmlElement *bndbox = new TiXmlElement("bndbox");
					objects->LinkEndChild(bndbox);
					{
						ss.clear();
						ss << obj.bboxes[i].xmin;
						ss >> tempStr;
						TiXmlElement *xmin = new TiXmlElement("xmin");
						bndbox->LinkEndChild(xmin);
						TiXmlText *xminContent = new TiXmlText(tempStr.c_str());
						xmin->LinkEndChild(xminContent);
						//---------------------
						ss.clear();
						ss << obj.bboxes[i].ymin;
						ss >> tempStr;
						TiXmlElement *ymin = new TiXmlElement("ymin");
						bndbox->LinkEndChild(ymin);
						TiXmlText *yminContent = new TiXmlText(tempStr.c_str());
						ymin->LinkEndChild(yminContent);
						//---------------------
						ss.clear();
						ss << obj.bboxes[i].xmax;
						ss >> tempStr;
						TiXmlElement *xmax = new TiXmlElement("xmax");
						bndbox->LinkEndChild(xmax);
						TiXmlText *xmaxContent = new TiXmlText(tempStr.c_str());
						xmax->LinkEndChild(xmaxContent);
						//---------------------
						ss.clear();
						ss << obj.bboxes[i].ymax;
						ss >> tempStr;
						TiXmlElement *ymax = new TiXmlElement("ymax");
						bndbox->LinkEndChild(ymax);
						TiXmlText *ymaxContent = new TiXmlText(tempStr.c_str());
						ymax->LinkEndChild(ymaxContent);
					}
				}

			}
		}

	}
	int index = obj.file_name.find_last_of('.');
	filename = "./xmls/" + obj.file_name.substr(0, index) + ".xml";
	myDocument->SaveFile(filename.c_str());
	delete myDocument; //delete root node is just ok
}

//字符串分割函数
vector<string> split(string str, string pattern){
	vector<string> ret;
	if (pattern.empty()) return ret;
	size_t start = 0, index = str.find_first_of(pattern, 0);
	while (index != str.npos){
		if (start != index)
			ret.push_back(str.substr(start, index - start));
		start = index + 1;
		index = str.find_first_of(pattern, start);
	}
	if (!str.substr(start).empty())
		ret.push_back(str.substr(start));
	return ret;
}

void convertFromFile(){
	//获取行数据
	fstream infile("boundingboxes.txt");
	std::string line;
	while (!infile.eof()){
		getline(infile, line);
		if (line.empty())
			continue;
		std::string pattern = "	";
		vector<string> line_split = split(line, pattern);
		int num = std::stoi(line_split[1]);
		vector<string> fpath_split = split(line_split[0], "/");
		std::string fname = fpath_split[fpath_split.size() - 1];
		//xml
		IMAGE_OBJECT obj;
		obj.folder_name = "VOC2012";
		obj.database_name = "The VOC2007 Database";
		obj.image_source = "flickr";
		obj.image_id = "";
		obj.flickr_id = "Fried Camels";
		obj.flickr_name = "Jinky the Fruit Bat";
		obj.size_width = 500;
		obj.size_height = 600;
		obj.size_depth = 1;
		obj.annotation = "PASCAL VOC2007";
		obj.file_name = fname;
		obj.segmented = "0";
		for (int i = 0; i < num; ++i){						
			coords coords_obj;
			coords_obj.difficult = "0";
			coords_obj.truncated = "1";
			coords_obj.pose = "";
			coords_obj.name = line_split[2 + i * 5];
			coords_obj.xmin = std::stoi(line_split[3 + i * 5]);
			coords_obj.ymin = std::stoi(line_split[4 + i * 5]);
			coords_obj.xmax = std::stoi(line_split[5 + i * 5]);
			coords_obj.ymax = std::stoi(line_split[6 + i * 5]);
			obj.bboxes.push_back(coords_obj);		
		}
		annotate(obj);
	}
	infile.close();
}

int main()
{
	convertFromFile();

	return 0;
}