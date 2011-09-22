/* Auto-generated by genmsg_cpp for file /home/klc/Code/skynetish.com/ros/stacks/my_stack/my_teleop/msg/State.msg */
#ifndef MY_TELEOP_MESSAGE_STATE_H
#define MY_TELEOP_MESSAGE_STATE_H
#include <string>
#include <vector>
#include <ostream>
#include "ros/serialization.h"
#include "ros/builtin_message_traits.h"
#include "ros/message_operations.h"
#include "ros/message.h"
#include "ros/time.h"

#include "my_teleop/Axis.h"
#include "my_teleop/Button.h"

namespace my_teleop
{
template <class ContainerAllocator>
struct State_ : public ros::Message
{
  typedef State_<ContainerAllocator> Type;

  State_()
  : axes()
  , buttons()
  {
  }

  State_(const ContainerAllocator& _alloc)
  : axes(_alloc)
  , buttons(_alloc)
  {
  }

  typedef std::vector< ::my_teleop::Axis_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::my_teleop::Axis_<ContainerAllocator> >::other >  _axes_type;
  std::vector< ::my_teleop::Axis_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::my_teleop::Axis_<ContainerAllocator> >::other >  axes;

  typedef std::vector< ::my_teleop::Button_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::my_teleop::Button_<ContainerAllocator> >::other >  _buttons_type;
  std::vector< ::my_teleop::Button_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::my_teleop::Button_<ContainerAllocator> >::other >  buttons;


  ROS_DEPRECATED uint32_t get_axes_size() const { return (uint32_t)axes.size(); }
  ROS_DEPRECATED void set_axes_size(uint32_t size) { axes.resize((size_t)size); }
  ROS_DEPRECATED void get_axes_vec(std::vector< ::my_teleop::Axis_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::my_teleop::Axis_<ContainerAllocator> >::other > & vec) const { vec = this->axes; }
  ROS_DEPRECATED void set_axes_vec(const std::vector< ::my_teleop::Axis_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::my_teleop::Axis_<ContainerAllocator> >::other > & vec) { this->axes = vec; }
  ROS_DEPRECATED uint32_t get_buttons_size() const { return (uint32_t)buttons.size(); }
  ROS_DEPRECATED void set_buttons_size(uint32_t size) { buttons.resize((size_t)size); }
  ROS_DEPRECATED void get_buttons_vec(std::vector< ::my_teleop::Button_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::my_teleop::Button_<ContainerAllocator> >::other > & vec) const { vec = this->buttons; }
  ROS_DEPRECATED void set_buttons_vec(const std::vector< ::my_teleop::Button_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::my_teleop::Button_<ContainerAllocator> >::other > & vec) { this->buttons = vec; }
private:
  static const char* __s_getDataType_() { return "my_teleop/State"; }
public:
  ROS_DEPRECATED static const std::string __s_getDataType() { return __s_getDataType_(); }

  ROS_DEPRECATED const std::string __getDataType() const { return __s_getDataType_(); }

private:
  static const char* __s_getMD5Sum_() { return "169b20224a7dd29b091cc66ab41be2e0"; }
public:
  ROS_DEPRECATED static const std::string __s_getMD5Sum() { return __s_getMD5Sum_(); }

  ROS_DEPRECATED const std::string __getMD5Sum() const { return __s_getMD5Sum_(); }

private:
  static const char* __s_getMessageDefinition_() { return "Axis[] axes\n\
Button[] buttons\n\
\n\
================================================================================\n\
MSG: my_teleop/Axis\n\
int32 type\n\
float32 value\n\
\n\
================================================================================\n\
MSG: my_teleop/Button\n\
int32 type\n\
int32 value\n\
\n\
"; }
public:
  ROS_DEPRECATED static const std::string __s_getMessageDefinition() { return __s_getMessageDefinition_(); }

  ROS_DEPRECATED const std::string __getMessageDefinition() const { return __s_getMessageDefinition_(); }

  ROS_DEPRECATED virtual uint8_t *serialize(uint8_t *write_ptr, uint32_t seq) const
  {
    ros::serialization::OStream stream(write_ptr, 1000000000);
    ros::serialization::serialize(stream, axes);
    ros::serialization::serialize(stream, buttons);
    return stream.getData();
  }

  ROS_DEPRECATED virtual uint8_t *deserialize(uint8_t *read_ptr)
  {
    ros::serialization::IStream stream(read_ptr, 1000000000);
    ros::serialization::deserialize(stream, axes);
    ros::serialization::deserialize(stream, buttons);
    return stream.getData();
  }

  ROS_DEPRECATED virtual uint32_t serializationLength() const
  {
    uint32_t size = 0;
    size += ros::serialization::serializationLength(axes);
    size += ros::serialization::serializationLength(buttons);
    return size;
  }

  typedef boost::shared_ptr< ::my_teleop::State_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::my_teleop::State_<ContainerAllocator>  const> ConstPtr;
}; // struct State
typedef  ::my_teleop::State_<std::allocator<void> > State;

typedef boost::shared_ptr< ::my_teleop::State> StatePtr;
typedef boost::shared_ptr< ::my_teleop::State const> StateConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::my_teleop::State_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::my_teleop::State_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace my_teleop

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator>
struct MD5Sum< ::my_teleop::State_<ContainerAllocator> > {
  static const char* value() 
  {
    return "169b20224a7dd29b091cc66ab41be2e0";
  }

  static const char* value(const  ::my_teleop::State_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x169b20224a7dd29bULL;
  static const uint64_t static_value2 = 0x091cc66ab41be2e0ULL;
};

template<class ContainerAllocator>
struct DataType< ::my_teleop::State_<ContainerAllocator> > {
  static const char* value() 
  {
    return "my_teleop/State";
  }

  static const char* value(const  ::my_teleop::State_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::my_teleop::State_<ContainerAllocator> > {
  static const char* value() 
  {
    return "Axis[] axes\n\
Button[] buttons\n\
\n\
================================================================================\n\
MSG: my_teleop/Axis\n\
int32 type\n\
float32 value\n\
\n\
================================================================================\n\
MSG: my_teleop/Button\n\
int32 type\n\
int32 value\n\
\n\
";
  }

  static const char* value(const  ::my_teleop::State_<ContainerAllocator> &) { return value(); } 
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::my_teleop::State_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.axes);
    stream.next(m.buttons);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct State_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::my_teleop::State_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::my_teleop::State_<ContainerAllocator> & v) 
  {
    s << indent << "axes[]" << std::endl;
    for (size_t i = 0; i < v.axes.size(); ++i)
    {
      s << indent << "  axes[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::my_teleop::Axis_<ContainerAllocator> >::stream(s, indent + "    ", v.axes[i]);
    }
    s << indent << "buttons[]" << std::endl;
    for (size_t i = 0; i < v.buttons.size(); ++i)
    {
      s << indent << "  buttons[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::my_teleop::Button_<ContainerAllocator> >::stream(s, indent + "    ", v.buttons[i]);
    }
  }
};


} // namespace message_operations
} // namespace ros

#endif // MY_TELEOP_MESSAGE_STATE_H

