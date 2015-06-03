/****************************************************************************
** Meta object code from reading C++ file 'thirdplugindlg.h'
**
** Created: Wed May 20 21:08:02 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../thirdplugindlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'thirdplugindlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ThirdPluginDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x08,
      45,   15,   15,   15, 0x08,
      77,   15,   15,   15, 0x08,
     114,  109,   15,   15, 0x08,
     176,  164,   15,   15, 0x08,
     239,  164,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ThirdPluginDlg[] = {
    "ThirdPluginDlg\0\0OnBtnAddThirdPluginClicked()\0"
    "OnBtnUpdateThirdPluginClicked()\0"
    "OnBtnDeleteThirdPluginClicked()\0item\0"
    "OnTbThirdPluginListItemClicked(QTableWidgetItem*)\0"
    "item,column\0"
    "OnTrThirdPluginFileListItemDoubleClicked(QTreeWidgetItem*,int)\0"
    "OnTrThirdPluginFileListItemClicked(QTreeWidgetItem*,int)\0"
};

void ThirdPluginDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ThirdPluginDlg *_t = static_cast<ThirdPluginDlg *>(_o);
        switch (_id) {
        case 0: _t->OnBtnAddThirdPluginClicked(); break;
        case 1: _t->OnBtnUpdateThirdPluginClicked(); break;
        case 2: _t->OnBtnDeleteThirdPluginClicked(); break;
        case 3: _t->OnTbThirdPluginListItemClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 4: _t->OnTrThirdPluginFileListItemDoubleClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->OnTrThirdPluginFileListItemClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ThirdPluginDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ThirdPluginDlg::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ThirdPluginDlg,
      qt_meta_data_ThirdPluginDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ThirdPluginDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ThirdPluginDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ThirdPluginDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ThirdPluginDlg))
        return static_cast<void*>(const_cast< ThirdPluginDlg*>(this));
    return QWidget::qt_metacast(_clname);
}

int ThirdPluginDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
