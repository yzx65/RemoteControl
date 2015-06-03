/****************************************************************************
** Meta object code from reading C++ file 'uploadthirdplugindlg.h'
**
** Created: Tue Mar 31 10:16:05 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../uploadthirdplugindlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uploadthirdplugindlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_UploadThirdPluginDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      22,   21,   21,   21, 0x08,
      44,   21,   21,   21, 0x08,
      61,   21,   21,   21, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_UploadThirdPluginDlg[] = {
    "UploadThirdPluginDlg\0\0onBtnGetPathClicked()\0"
    "onBtnOKclicked()\0onBtnAdvanceClicked()\0"
};

void UploadThirdPluginDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        UploadThirdPluginDlg *_t = static_cast<UploadThirdPluginDlg *>(_o);
        switch (_id) {
        case 0: _t->onBtnGetPathClicked(); break;
        case 1: _t->onBtnOKclicked(); break;
        case 2: _t->onBtnAdvanceClicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData UploadThirdPluginDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject UploadThirdPluginDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_UploadThirdPluginDlg,
      qt_meta_data_UploadThirdPluginDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &UploadThirdPluginDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *UploadThirdPluginDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *UploadThirdPluginDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UploadThirdPluginDlg))
        return static_cast<void*>(const_cast< UploadThirdPluginDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int UploadThirdPluginDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
