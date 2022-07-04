/****************************************************************************
** Meta object code from reading C++ file 'imu_to_joint_panel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../can_imu_rviz_plugin/src/imu_to_joint_panel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imu_to_joint_panel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_imu_to_joint_rviz_plugin__ImuToJointPanel_t {
    QByteArrayData data[26];
    char stringdata0[437];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_imu_to_joint_rviz_plugin__ImuToJointPanel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_imu_to_joint_rviz_plugin__ImuToJointPanel_t qt_meta_stringdata_imu_to_joint_rviz_plugin__ImuToJointPanel = {
    {
QT_MOC_LITERAL(0, 0, 41), // "imu_to_joint_rviz_plugin::Imu..."
QT_MOC_LITERAL(1, 42, 14), // "euler_callback"
QT_MOC_LITERAL(2, 57, 0), // ""
QT_MOC_LITERAL(3, 58, 36), // "can_imu_lws::IMU_Euler_msg::C..."
QT_MOC_LITERAL(4, 95, 9), // "euler_msg"
QT_MOC_LITERAL(5, 105, 10), // "imu_id_set"
QT_MOC_LITERAL(6, 116, 9), // "startSpin"
QT_MOC_LITERAL(7, 126, 16), // "set_joint_offset"
QT_MOC_LITERAL(8, 143, 15), // "set_joint_state"
QT_MOC_LITERAL(9, 159, 24), // "sensor_msgs::JointState&"
QT_MOC_LITERAL(10, 184, 15), // "joint_state_msg"
QT_MOC_LITERAL(11, 200, 16), // "test_joint_state"
QT_MOC_LITERAL(12, 217, 16), // "imu_start_listen"
QT_MOC_LITERAL(13, 234, 15), // "joint_state_pub"
QT_MOC_LITERAL(14, 250, 15), // "euler_to_radian"
QT_MOC_LITERAL(15, 266, 5), // "euler"
QT_MOC_LITERAL(16, 272, 9), // "checkTest"
QT_MOC_LITERAL(17, 282, 15), // "open_can_device"
QT_MOC_LITERAL(18, 298, 16), // "close_can_device"
QT_MOC_LITERAL(19, 315, 21), // "start_can_msg_receive"
QT_MOC_LITERAL(20, 337, 22), // "can_device_config_init"
QT_MOC_LITERAL(21, 360, 4), // "Baud"
QT_MOC_LITERAL(22, 365, 15), // "can_msg_receive"
QT_MOC_LITERAL(23, 381, 24), // "thread_channel_1_receive"
QT_MOC_LITERAL(24, 406, 5), // "param"
QT_MOC_LITERAL(25, 412, 24) // "thread_channel_2_receive"

    },
    "imu_to_joint_rviz_plugin::ImuToJointPanel\0"
    "euler_callback\0\0can_imu_lws::IMU_Euler_msg::ConstPtr\0"
    "euler_msg\0imu_id_set\0startSpin\0"
    "set_joint_offset\0set_joint_state\0"
    "sensor_msgs::JointState&\0joint_state_msg\0"
    "test_joint_state\0imu_start_listen\0"
    "joint_state_pub\0euler_to_radian\0euler\0"
    "checkTest\0open_can_device\0close_can_device\0"
    "start_can_msg_receive\0can_device_config_init\0"
    "Baud\0can_msg_receive\0thread_channel_1_receive\0"
    "param\0thread_channel_2_receive"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_imu_to_joint_rviz_plugin__ImuToJointPanel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   99,    2, 0x09 /* Protected */,
       5,    0,  102,    2, 0x09 /* Protected */,
       6,    0,  103,    2, 0x09 /* Protected */,
       7,    0,  104,    2, 0x09 /* Protected */,
       8,    1,  105,    2, 0x09 /* Protected */,
      11,    1,  108,    2, 0x09 /* Protected */,
      12,    0,  111,    2, 0x09 /* Protected */,
      13,    0,  112,    2, 0x09 /* Protected */,
      14,    1,  113,    2, 0x09 /* Protected */,
      16,    0,  116,    2, 0x09 /* Protected */,
      17,    0,  117,    2, 0x09 /* Protected */,
      18,    0,  118,    2, 0x09 /* Protected */,
      19,    0,  119,    2, 0x09 /* Protected */,
      20,    1,  120,    2, 0x09 /* Protected */,
      22,    0,  123,    2, 0x09 /* Protected */,
      23,    1,  124,    2, 0x09 /* Protected */,
      25,    1,  127,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Float, QMetaType::Float,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   21,
    QMetaType::Void,
    QMetaType::VoidStar, QMetaType::VoidStar,   24,
    QMetaType::VoidStar, QMetaType::VoidStar,   24,

       0        // eod
};

void imu_to_joint_rviz_plugin::ImuToJointPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ImuToJointPanel *_t = static_cast<ImuToJointPanel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->euler_callback((*reinterpret_cast< const can_imu_lws::IMU_Euler_msg::ConstPtr(*)>(_a[1]))); break;
        case 1: _t->imu_id_set(); break;
        case 2: _t->startSpin(); break;
        case 3: _t->set_joint_offset(); break;
        case 4: _t->set_joint_state((*reinterpret_cast< sensor_msgs::JointState(*)>(_a[1]))); break;
        case 5: _t->test_joint_state((*reinterpret_cast< sensor_msgs::JointState(*)>(_a[1]))); break;
        case 6: _t->imu_start_listen(); break;
        case 7: _t->joint_state_pub(); break;
        case 8: { float _r = _t->euler_to_radian((*reinterpret_cast< float(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 9: _t->checkTest(); break;
        case 10: _t->open_can_device(); break;
        case 11: _t->close_can_device(); break;
        case 12: _t->start_can_msg_receive(); break;
        case 13: _t->can_device_config_init((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->can_msg_receive(); break;
        case 15: { void* _r = _t->thread_channel_1_receive((*reinterpret_cast< void*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< void**>(_a[0]) = std::move(_r); }  break;
        case 16: { void* _r = _t->thread_channel_2_receive((*reinterpret_cast< void*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< void**>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

const QMetaObject imu_to_joint_rviz_plugin::ImuToJointPanel::staticMetaObject = {
    { &rviz::Panel::staticMetaObject, qt_meta_stringdata_imu_to_joint_rviz_plugin__ImuToJointPanel.data,
      qt_meta_data_imu_to_joint_rviz_plugin__ImuToJointPanel,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *imu_to_joint_rviz_plugin::ImuToJointPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *imu_to_joint_rviz_plugin::ImuToJointPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_imu_to_joint_rviz_plugin__ImuToJointPanel.stringdata0))
        return static_cast<void*>(this);
    return rviz::Panel::qt_metacast(_clname);
}

int imu_to_joint_rviz_plugin::ImuToJointPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = rviz::Panel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
