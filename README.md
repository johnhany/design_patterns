# design_patterns

C++实现的22种设计模式

代码参考自[《深入设计模式》](https://refactoring.guru/design-patterns)

为了便于理解，所有代码以机器学习模型的构建\训练过程为例

## 创建型模式（Creational patterns）

主要关注对象创建过程的灵活性和可复用性。

### 工厂方法（Factory method）

适用于将对象的创建和使用分离，并希望尽可能多地复用现有代码来处理新型对象的情景。`工厂方法模式`可以演化为`抽象工厂模式`、`生成器模式`和`原型模式`。

### 抽象工厂（Abstract factory）

适用于需要创建许多种一系列相互依赖的对象的情景。`工厂方法`与`抽象工厂`的根本区别在于`工厂方法`是“方法”，`抽象工厂`是“对象”。具体地，`工厂方法`的目的在于用基类的不同子类来表示不同的对象；`抽象工厂`只需要关心如何创建一系列相互依赖的对象，可以理解为一种包含很多`工厂方法`的对象。

### 生成器（Builder）

适用于需要分很多步骤创建不同对象的情景。

### 原型（Prototype）

适用于需要复制复杂的对象，并希望新复制的对象独立于原来的代码的情景。

### 单例（Singleton）

适用于一个类只需要一个实例的情景。但多线程下不能保证所有线程只有一个实例（C++11之前）。`抽象工厂模式`、`生成器模式`和`原型模式`都可以用`单例`实现。

## 结构型模式（Structural patterns）

### 适配器（Adapter）

适用于使现有代码调用不兼容的类（比如遗留代码、第三方库等）。

### 桥接（Bridge）

适用于需要按照若干维度的多个属性扩展现有类，或者在运行时切换不同实现方式的情景。典型的桥接模式把原问题拆分为抽象和实现两个结构，实现负责提供底层的、具体的单元操作（比如跨平台的底层驱动），抽象负责在实现的基础之上执行高阶的操作（比如程序的GUI层）。通过不同实现和抽象的组合实现更丰富的行为。

### 组合（Composite）

适用于需要以树状结构表示对象之间关系的情景。树由两种元素构成：简单叶子元素和容器元素，其中容器元素必须能够包含叶子元素和其他容器元素。所有元素共用相同的接口，容器的接口只需要关心如何把其元素返回的结果合并起来，具体的接口细节由叶子元素实现。

### 装饰（Decorator）

适用于在不修改原始接口的前提下增加新功能的情景，尤其是原始接口被声明为`final`时。

### 外观（Facade）

适用于需要用一个简洁的接口来协调多个类的复杂行为的情景。注意外观类自身容易和很多个类耦合。

### 享元（Flyweight）

适用于需要在有限内存保留大量相似对象的情景，尤其是对象之间存在重复的属性时。

### 代理（Proxy）

适用于允许延迟调用一个十分耗费资源的复杂对象的情景。可以在不修改服务对象的前提下，增加缓存、日志等功能。

## 行为模式（Behavioral patterns）

### 责任链（Chain of responsibility）

适用于以不同方式处理请求，但处理请求的顺序事先未知或需要在运行时调整顺序的情景。

### 命令（Command）

用来把某种请求封装为具体的对象，以实现多个请求的队列、日志、取消等功能。

### 迭代器（Iterator）

用来提供遍历容器内部元素的接口。元素的遍历策略由容器的开发者来设计，容器的调用者不需要关心遍历策略的细节。

### 中介者（Mediator）

适用于多个类之间紧密耦合，每次增加新功能需要修改大量代码的情景。可以使各组件不再关心其他组件的细节，把复杂的依赖关系交给中介者处理。

### 备忘录（Memento）

适用于需要记录对象快照来恢复其历史状态的情景。可以用来实现“撤销”某操作的效果。

### 观察者（Observer）

适用于有很多对象都能以“订阅”的方式同时接收某个类发出的信息，而且随时可以取消或增加订阅的情景。

### 状态（State）

适用于需要通过改变对象内部状态来改变其行为的情景。一般将包含很多`if`/`switch`分支的函数改写为对象时都可以用到状态模式。

### 策略（Strategy）

适用于需要把业务逻辑与具体算法隔离、或者在运行时切换算法的情景。

### 模板方法（Template method）

适用于需要把多个针对不同对象的算法过程合并在一个类当中，而且这些过程的大部分步骤都相同的情景。`模板方法`模式是静态的，即通过继承的方式在编译时确定所采取的算法步骤。`策略`模式是动态的，即在运行时确定所采取的算法步骤（且允许在运行时切换算法）。

### 访问者（Visitor）

适用于需要用某种操作处理一个对象中所有元素的情景，尤其是需要将操作的实现与对象自身分离，以便在不影响对象结构的前提下改变这种操作的行为时。与其他可以在运行时切换操作行为的模式相比（比如`命令`模式或`策略`模式），`访问者`模式的特点是只有在运行期间访问者与被访问者的类型同时满足条件时才会执行操作。
