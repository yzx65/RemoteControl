/****************************************************************************
** Meta object code from reading C++ file 'filectrldlg.h'
**
** Created: Sun Jun 7 18:52:39 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../filectrldlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'filectrldlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FileCtrlDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   13,   12,   12, 0x08,
      58,   13,   12,   12, 0x08,
     102,   97,   12,   12, 0x08,
     143,   97,   12,   12, 0x08,
     204,  192,   12,   12, 0x08,
     254,  248,   12,   12, 0x08,
     281,   12,   12,   12, 0x08,
     300,   12,   12,   12, 0x08,
     323,   12,   12,   12, 0x08,
     344,   12,   12,   12, 0x08,
     367,   12,   12,   12, 0x08,
     393,   12,   12,   12, 0x08,
     418,   12,   12,   12, 0x08,
     435,   12,   12,   12, 0x08,
     457,   12,   12,   12, 0x08,
     478,   12,   12,   12, 0x08,
     496,   12,   12,   12, 0x08,
     518,   12,   12,   12, 0x08,
     540,   12,   12,   12, 0x08,
     561,   12,   12,   12, 0x08,
     587,   12,   12,   12, 0x08,
     615,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FileCtrlDlg[] = {
    "FileCtrlDlg\0\0point\0"
    "onTbFileListContextMenuActived(QPoint)\0"
    "onTrFileCtrlContextMenuActived(QPoint)\0"
    "item\0onTbFileListItemClick(QTableWidgetItem*)\0"
    "onTbFileListItemDoubleClicked(QTableWidgetItem*)\0"
    "item,column\0onTrFileCtrlItemClick(QTreeWidgetItem*,int)\0"
    "index\0onAddressIndexChanged(int)\0"
    "onBtnGotoClicked()\0onBtnFavoriteClicked()\0"
    "onBtnUploadClicked()\0onBtnDownloadClicked()\0"
    "onBtnDownloadDirClicked()\0"
    "onBtnGetDirListClicked()\0onBtnUpClicked()\0"
    "onBtnRefreshClicked()\0onBtnDeleteClicked()\0"
    "onBtnRunClicked()\0onBtnAnalyzeClicked()\0"
    "onBtnMonitorClicked()\0onBtnSearchClicked()\0"
    "onBtnStartSearchClicked()\0"
    "onBtnStartDownloadClicked()\0"
    "onBtnReturnFileListClicked()\0"
};

void FileCtrlDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FileCtrlDlg *_t = static_cast<FileCtrlDlg *>(_o);
        switch (_id) {
        case 0: _t->onTbFileListContextMenuActived((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 1: _t->onTrFileCtrlContextMenuActived((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 2: _t->onTbFileListItemClick((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 3: _t->onTbFileListItemDoubleClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 4: _t->onTrFileCtrlItemClick((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->onAddressIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->onBtnGotoClicked(); break;
        case 7: _t->onBtnFavoriteClicked(); break;
        case 8: _t->onBtnUploadClicked(); break;
        case 9: _t->onBtnDownloadClicked(); break;
        case 10: _t->onBtnDownloadDirClicked(); break;
        case 11: _t->onBtnGetDirListClicked(); break;
        case 12: _t->onBtnUpClicked(); break;
        case 13: _t->onBtnRefreshClicked(); break;
        case 14: _t->onBtnDeleteClicked(); break;
        case 15: _t->onBtnRunClicked(); break;
        case 16: _t->onBtnAnalyzeClicked(); break;
        case 17: _t->onBtnMonitorClicked(); break;
        case 18: _t->onBtnSearchClicked(); break;
        case 19: _t->onBtnStartSearchClicked(); break;
        case 20: _t->onBtnStartDownloadClicked(); break;
        case 21: _t->onBtnReturnFileListClicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FileCtrlDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FileCtrlDlg::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FileCtrlDlg,
      qt_meta_data_FileCtrlDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FileCtrlDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FileCtrlDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FileCtrlDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FileCtrlDlg))
        return static_cast<void*>(const_cast< FileCtrlDlg*>(this));
    return QWidget::qt_metacast(_clname);
}

int FileCtrlDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
