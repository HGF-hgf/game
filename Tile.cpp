#include"Tile.h"
#include"Texture.h"

using namespace std;
Tile::Tile(int tilesize, int rowcount, int colcount, TileMap tilemap, TilesetList tilesets)
	: m_Tilesize(tilesize), m_ColCount(colcount), m_RowCount(rowcount), m_TileMap(tilemap), m_Tilesets(tilesets) {
	
	for (unsigned int i = 0; i < m_Tilesets.size(); i++) {
		Texture::Getinstance()->LoadTexture(m_Tilesets[i].Name, "texture/map/" + m_Tilesets[i].Source);
	}

}

void Tile::Render() {
	for (unsigned int i = 0;i < m_RowCount;i++) {
		for (unsigned int j = 0; j < m_ColCount;j++) {
			int tileID = m_TileMap[i][j];
			//int temp = tileID;

			if (tileID == 0)
				continue;
			else {
				int index = 0 ;
				if (m_Tilesets.size() > 1) {
					for (unsigned int k = 1; k < m_Tilesets.size();k++) {
						if (tileID >= m_Tilesets[k].FirstID && tileID <= m_Tilesets[k].LastID) {
							tileID = tileID + m_Tilesets[k].TileCount - m_Tilesets[k].LastID;
							index = k;
							break;
						}
					}
				}

				Tileset ts = m_Tilesets[index];
				int tileRow = tileID / ts.ColCount;
				int tileCol = tileID - tileRow * ts.ColCount - 1;

				if (tileID % ts.ColCount == 0) {
					tileRow--;
					tileCol = ts.ColCount - 1;
				}
				Texture::Getinstance()->DrawTile(ts.Name, ts.Tilesize, j * ts.Tilesize, i * ts.Tilesize, tileRow, tileCol);
			}
		}
	}
}

void Tile::Update() {

}