/****************************************************************************
** Meta object code from reading C++ file 'mapinfodlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mapinfodlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mapinfodlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MapInfoDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   12,   11,   11, 0x08,
      67,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MapInfoDlg[] = {
    "MapInfoDlg\0\0item\0"
    "onTbLocationHistoryItemClicked(QTableWidgetItem*)\0"
    "onBtnGetLocationClicked()\0"
};

void MapInfoDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MapInfoDlg *_t = static_cast<MapInfoDlg *>(_o);
        switch (_id) {
        case 0: _t->onTbLocationHistoryItemClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 1: _t->onBtnGetLocationClicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MapInfoDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MapInfoDlg::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MapInfoDlg,
      qt_meta_data_MapInfoDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MapInfoDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MapInfoDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MapInfoDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MapInfoDlg))
        return static_cast<void*>(const_cast< MapInfoDlg*>(this));
    return QWidget::qt_metacast(_clname);
}

int MapInfoDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
