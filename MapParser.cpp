#include"MapParser.h"

using namespace std;

MapParser* MapParser::s_Instance = nullptr;

bool MapParser::Load() {
	if(!Parse("Level1", "texture/map/map2.tmx"))
		return false;
	return true;
}



bool MapParser::Parse(string id, string source) {
	TiXmlDocument xml;
	xml.LoadFile(source);
	if (xml.Error()) {
		cerr << "Failed to load" << source << endl;
		return false;
	}

	TiXmlElement* root = xml.RootElement();
	int rowcount, colcount, tilesize = 0;
	root->Attribute("width", &colcount);
	root->Attribute("height", &rowcount);
	root->Attribute("tilewidth", &tilesize);


	//Parse tileset
	TilesetList tilesets;
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if (e->Value() == string("tileset")) {
			tilesets.push_back(ParseTileset(e));
		}
	}

	//Parse Layer
	Map* gamemap = new Map();
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()){
		if (e->Value() == string("layer")) {
			Tile* tilelayer = ParseTileLayer(e, tilesets, tilesize, rowcount, colcount);
			gamemap->m_MapLayer.push_back(tilelayer);
		}
	}

	m_MapDict[id] = gamemap;
	return true;
}

Tileset MapParser::ParseTileset(TiXmlElement* xmlTileset) {
	Tileset tileset;
	tileset.Name = xmlTileset->Attribute("name");
	xmlTileset->Attribute("firstgid", &tileset.FirstID);
	xmlTileset->Attribute("tilecount", &tileset.TileCount);
	tileset.LastID = (tileset.FirstID + tileset.TileCount) - 1;

	xmlTileset->Attribute("columns", &tileset.ColCount);
	tileset.RowCount = tileset.TileCount / tileset.ColCount;
	xmlTileset->Attribute("tilewidth", &tileset.Tilesize);

	TiXmlElement* image = xmlTileset->FirstChildElement();
	tileset.Source = image->Attribute("source");
	return tileset;

}

Tile* MapParser::ParseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesets, int tilesize, int rowcount, int colcount) {
	TiXmlElement* data = nullptr;
	for (TiXmlElement* e = xmlLayer->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if (e->Value() == string("data")) {
			data = e;
			break;
		}
	}

	string matrix(data->GetText());
	istringstream iss(matrix);
	string id;

	TileMap tilemap(rowcount, vector<int>(colcount, 0));

	for (int row = 0; row < rowcount; row++) {
		for (int col = 0; col < colcount; col++) {
			getline(iss, id, ',');
			stringstream convertor(id);
			convertor >> tilemap[row][col];

			if (!iss.good())
				break;
		}
	}

	return (new Tile(tilesize, rowcount, colcount, tilemap, tilesets));
}

void MapParser::Clean() {
	map<string, Map*>::iterator it;
	for (it = m_MapDict.begin(); it != m_MapDict.end();it++)
		it->second = nullptr;

	m_MapDict.clear();
}