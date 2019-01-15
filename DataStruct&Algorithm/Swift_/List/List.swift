//
//  List.swift
//  Swift
//
//  Created by K K on 2018/12/5.
//  Copyright © 2018 K K. All rights reserved.
//

import Foundation


/// 节点
class Node<T> {
    var value: T
    var next: Node?
    
    init(_ value: T) {
        self.value = value
        next = nil
    }
}


enum NodeLocal {
    case pre
    case current
    case next
}


class List<T> {
    var head: Node<T>?
    var tail: Node<T>?
    var size: Int
    
    
    /// 构造
    init() {
        size = 0
        head = nil
        tail = nil
    }
    
    
    
    /// 插入节点数据
    ///
    /// - Parameters:
    ///   - node: 对应的节点
    ///   - vaule: 要插入的数据
    /// - Returns: 返回插入的节点
    func insertNode(node: Node<T>?, vaule: T) -> Node<T> {
        let new = Node<T>(vaule)
        if node == nil {
            if head == nil {
                // 链表中元素为空，插入到头部
                head = new
                tail = new
            } else {
                // 链表中有元素，插入到尾部
                tail?.next = new
                tail = new
            }
        } else {
            // 插入到节点的后面
            new.next = node?.next
            node?.next = new
            if new.next == nil {
                tail = new
            }
        }
        size += 1
        return new
    }
    
    
    
    /// 删除数据
    ///
    /// - Parameters:
    ///   - node: 删除的节点
    func removeNodeNext(node: Node<T>?) -> Node<T>? {
        if size == 0 {
            return nil
        }
        var delete = node?.next
        guard let node = node else {
            // 删除头部元素
            delete = head
            head = head?.next
            size -= 1
            return nil
        }
        if node.next == nil {
            return nil
        }
        
        
        node.next = node.next?.next
        if node.next == nil {
            tail = node
        }
        size -= 1
        return delete
    }
    
    
    /// 链表反转
    func reserver() {
        // 少于两个元素，不处理
        if size < 2 {
            return
        }
        
        var next: Node<T>? = head?.next
        var nextN: Node<T>? = head?.next?.next
        
        // 将首元素先放到最后
        tail = head
        head?.next = nil
        
        while nextN != nil {
            // 将next插入到首元素的位置
            next?.next = head
            head = next
            
            // 将next进行下一轮赋值
            next = nextN
            nextN = next?.next
        }
        
        // 当next的next没有值的时候，进行到最后一个值的插入
        next?.next = head
        head = next
    }
    
    
    /// 析构
    func destory() {
        if size == 0 {
            return
        }
        
        while size > 0 {
            _ = removeNodeNext(node: nil)
        }
    }
    
    func display() {
        print("链表元素：\(size)个")
        var next: Node? = head
        while next != nil {
            print(next!.value)
            next = next?.next
        }
    }
}


func testIntList() {
    let list = List<Int>()
    list.display()
    
    _ = list.insertNode(node: nil, vaule: 10)
    list.display()
    _ = list.insertNode(node: nil, vaule: 20)
    list.display()
    let node3 = list.insertNode(node: nil, vaule: 30)
    list.display()
    _ = list.insertNode(node: nil, vaule: 40)
    list.display()
    _ = list.insertNode(node: nil, vaule: 50)
    list.display()
    
    print("链表反转-----------------------")
    list.reserver()
    list.display()
    
    print("链表再次反转-----------------------")
    list.reserver()
    list.display()
    
    print("删除第三个节点后面的一个节点-----------------")
    _ = list.removeNodeNext(node: node3)
    list.display()
    
    print("删除第一个节点后面的一个节点-----------------")
    _ = list.removeNodeNext(node: nil)
    list.display()
    
    
    print("删除所有列表-----------------")
    list.destory()
    list.display()
}


func testStringList() {
    let list = List<String>()
    _ = list.insertNode(node: nil, vaule: "aaaa")
    list.display()
    _ = list.insertNode(node: nil, vaule: "bbb")
    list.display()
    let node3 = list.insertNode(node: nil, vaule: "ccc")
    list.display()
    _ = list.insertNode(node: nil, vaule: "ddd")
    list.display()
    _ = list.insertNode(node: nil, vaule: "eee")
    list.display()
    
    print("链表反转-----------------------")
    list.reserver()
    list.display()
    
    print("链表再次反转-----------------------")
    list.reserver()
    list.display()
    
    print("删除第三个节点后面的一个节点-----------------")
    _ = list.removeNodeNext(node: node3)
    list.display()
    
    print("删除第一个节点后面的一个节点-----------------")
    _ = list.removeNodeNext(node: nil)
    list.display()
    
    
    print("删除所有列表-----------------")
    list.destory()
    list.display()
}
