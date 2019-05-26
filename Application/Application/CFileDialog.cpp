#include "CFileDialog.h"



CFileDialog::CFileDialog(QQuickWindow* window, CList* list, CImageProvider* provider)
	: IDialog(window),
	m_list(list),
	m_imageProvider(provider),
	temp_count(0),
	m_currentSelectedItem(-1)
{
}

CFileDialog::~CFileDialog()
{
	delete m_list, m_imageProvider;
}

void CFileDialog::Initialize()
{
}

void CFileDialog::getFiles(QList<QUrl> urls)
{
	for (int i = 0; i < urls.size(); ++i)
	{
		QString path = urls.at(i).toLocalFile();

		QString nameFile;

		for (int i = path.length() - 1; path[i] != '/' && 0 < i; --i) nameFile.insert(0, path[i]);

		CTagEditer tagEditer;
		Tags tags = tagEditer.GetTags(path);

		/*Item item;
		item.title = tags.Title;
		item.artist = tags.Artist;
		item.album = tags.Album;
		item.year = tags.Year;
		item.genre = tags.Genre;

		QFile image(Tools::absolutePath() + "/" + Tools::applicationName() + "/ArtCover.jpg");
		image.open(QIODevice::ReadOnly);
		QByteArray img = image.readAll();
		image.close();

		if (img.isEmpty())
		{
			QFile img("qrc:/Themes/White/standard_cover_x1000.jpg");
			img.open(QIODevice::ReadOnly);
			item.image = img.readAll();
			img.close();
		}
		else
		{
			item.image = img;
		}

		item.nameFile = nameFile;
		item.reserve = false;

		QFile file(path);
		file.open(QIODevice::ReadOnly);
		float fSize = (static_cast<float>(file.size())) / (1024 * 1024);
		int iSize = fSize * 100;
		float endSize = iSize * 0.01f;
		item.size = QString::number(endSize);
		file.close();

		m_list->AppendItem(item);

		m_urls.insert(nameFile, path);*/
	}
}

void CFileDialog::onFinishedProcess(int, QProcess::ExitStatus)
{

}

void CFileDialog::onClickedItem(QString fileName)
{
	QString path = m_urls.find(fileName).value();

	for (int i = 0; i < m_list->Size(); ++i)
	{
		if (m_list->At(i).nameFile == fileName)
		{
			m_currentSelectedItem = i;

			emit setTitle(m_list->At(i).title);
			emit setArtist(m_list->At(i).artist);
			emit setAlbum(m_list->At(i).album);
			emit setGenre(m_list->At(i).genre);
			emit setYear(m_list->At(i).year);

			QByteArray imageDAta = m_list->At(i).image;

			if (!imageDAta.isEmpty())
			{
				QImage image;
				image.loadFromData(imageDAta);

				m_imageProvider->DeleteList();
				m_imageProvider->AppendImage(image, QString::number(temp_count));

				emit setImage(QString::number(temp_count));

				++temp_count;
			}
			else
				emit setImage("standard_cover");

			isClickedColor();
			break;
		}
	}
}

void CFileDialog::onRemoveItem(QString fileName)
{
	for (int i = 0; i < m_list->Size(); ++i)
	{
		if (m_list->At(i).nameFile == fileName)
		{
			m_list->RemoveItem(i);
			break;
		}
	}
}

void CFileDialog::saveImage(QString path)
{
	if (m_currentSelectedItem >= 0)
	{
		Item item;

		item.nameFile = m_list->At(m_currentSelectedItem).nameFile;
		item.title = m_list->At(m_currentSelectedItem).title;
		item.artist = m_list->At(m_currentSelectedItem).artist;
		item.album = m_list->At(m_currentSelectedItem).album;
		item.year = m_list->At(m_currentSelectedItem).year;
		item.genre = m_list->At(m_currentSelectedItem).genre;
		item.size = m_list->At(m_currentSelectedItem).size;
		item.reserve = m_list->At(m_currentSelectedItem).reserve;

		QString localpath = path.remove(0, 8);
		item.image = localpath.toUtf8();

		m_list->RemoveItem(m_currentSelectedItem);
		m_list->InsertItem(m_currentSelectedItem, item);
	}
}

void CFileDialog::finish()
{
	/*CTable table;
	table.AddColumn("id");
	table.AddColumn("title");
	table.AddColumn("artist");
	table.AddColumn("album");
	table.AddColumn("genre");
	table.AddColumn("year");
	table.AddColumn("image");
	table.AddColumn("time");

	int id = 0;

	for (auto it : m_list->GetItems())
	{
		Row row;
		row.Append(id);
		row.Append(it.title);
		row.Append(it.artist);
		row.Append(it.album);
		row.Append(it.genre);
		row.Append(it.year);
		row.Append(it.image);
		row.Append(it.time);
		
		++id;

		QFile img(Tools::absolutePath() + "/" + Tools::applicationName() + "/ArtCover.jpg");
		img.open(QIODevice::WriteOnly);
		img.write(it.image);
		img.close();

		QStringList args;
		args << "-path";
		args << m_urls.find(it.nameFile).value();
		args << "-image";
		args << Tools::absolutePath() + "/" + Tools::applicationName() + "/ArtCover.jpg";
		args << "-title";
		args << it.title;
		args << "-artist";
		args << it.artist;
		args << "-album";
		args << it.album;
		args << "-genre";
		args << it.genre;
		args << "-year";
		args << it.year;

		QProcess cmd;
		cmd.startDetached(Tools::tagEditerPath(), args);

		table.AddRow(row);
	}*/
}

void CFileDialog::isClickedColor()
{
	if (m_currentSelectedItem >= 0)
	{
		for (int i = 0; i < m_list->Size(); ++i)
			if (m_list->At(i).reserve == true && i != m_currentSelectedItem)
			{
				Item item;

				item.nameFile = m_list->At(i).nameFile;
				item.title = m_list->At(i).title;
				item.artist = m_list->At(i).artist;
				item.album = m_list->At(i).album;
				item.year = m_list->At(i).year;
				item.genre = m_list->At(i).genre;
				item.size = m_list->At(i).size;
				item.image = m_list->At(i).image;
				item.reserve = false;

				m_list->RemoveItem(i);
				m_list->InsertItem(i, item);
			}

		if (m_list->At(m_currentSelectedItem).reserve == false)
		{
			Item item;

			item.nameFile = m_list->At(m_currentSelectedItem).nameFile;
			item.title = m_list->At(m_currentSelectedItem).title;
			item.artist = m_list->At(m_currentSelectedItem).artist;
			item.album = m_list->At(m_currentSelectedItem).album;
			item.year = m_list->At(m_currentSelectedItem).year;
			item.genre = m_list->At(m_currentSelectedItem).genre;
			item.size = m_list->At(m_currentSelectedItem).size;
			item.image = m_list->At(m_currentSelectedItem).image;
			item.reserve = true;

			m_list->RemoveItem(m_currentSelectedItem);
			m_list->InsertItem(m_currentSelectedItem, item);
		}
	}
}

void CFileDialog::saveFeatures(QString title, QString artist, QString album, QString genre, QString year)
{
	if (m_currentSelectedItem >= 0)
	{
		Item item;

		item.nameFile = m_list->At(m_currentSelectedItem).nameFile;
		item.image = m_list->At(m_currentSelectedItem).image;
		item.size = m_list->At(m_currentSelectedItem).size;
		item.reserve = m_list->At(m_currentSelectedItem).reserve;
		item.title = title;
		item.artist = artist;
		item.album = album;
		item.year = year;
		item.genre = genre;

		m_list->RemoveItem(m_currentSelectedItem);
		m_list->InsertItem(m_currentSelectedItem, item);
	}
}
