/****************************************************************************
** Meta object code from reading C++ file 'capturedlg.h'
**
** Created: Sun Sep 20 11:18:09 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../capturedlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'capturedlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CaptureDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      25,   11,   11,   11, 0x08,
      65,   53,   11,   11, 0x08,
     118,  113,   11,   11, 0x08,
     163,  113,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CaptureDlg[] = {
    "CaptureDlg\0\0emitModify()\0"
    "onBtnCaptureScreenClicked()\0item,column\0"
    "onTrScreenshotItemClicked(QTreeWidgetItem*,int)\0"
    "item\0onTbScreenshotItemClicked(QTableWidgetItem*)\0"
    "onTbScreenshotItemDoubleClicked(QTableWidgetItem*)\0"
};

void CaptureDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CaptureDlg *_t = static_cast<CaptureDlg *>(_o);
        switch (_id) {
        case 0: _t->emitModify(); break;
        case 1: _t->onBtnCaptureScreenClicked(); break;
        case 2: _t->onTrScreenshotItemClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->onTbScreenshotItemClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 4: _t->onTbScreenshotItemDoubleClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CaptureDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CaptureDlg::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CaptureDlg,
      qt_meta_data_CaptureDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CaptureDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CaptureDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CaptureDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CaptureDlg))
        return static_cast<void*>(const_cast< CaptureDlg*>(this));
    return QWidget::qt_metacast(_clname);
}

int CaptureDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void CaptureDlg::emitModify()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
