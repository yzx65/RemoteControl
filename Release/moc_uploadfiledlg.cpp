/****************************************************************************
** Meta object code from reading C++ file 'uploadfiledlg.h'
**
** Created: Mon Jun 15 20:54:29 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../uploadfiledlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uploadfiledlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_UploadFileDlg[] = {

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
      15,   14,   14,   14, 0x08,
      22,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_UploadFileDlg[] = {
    "UploadFileDlg\0\0OnOk()\0OnBtnBrowseClicked()\0"
};

void UploadFileDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        UploadFileDlg *_t = static_cast<UploadFileDlg *>(_o);
        switch (_id) {
        case 0: _t->OnOk(); break;
        case 1: _t->OnBtnBrowseClicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData UploadFileDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject UploadFileDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_UploadFileDlg,
      qt_meta_data_UploadFileDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &UploadFileDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *UploadFileDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *UploadFileDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UploadFileDlg))
        return static_cast<void*>(const_cast< UploadFileDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int UploadFileDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
