//
//  NSTreeNode+Additions.h
//  Amber
//
//  Created by Keith Duncan on 22/08/2007.
//  Copyright 2007 thirty-three. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface NSTreeNode (AFAdditions)
- (NSSet *)objectsAtIndexPaths:(NSArray *)indexPaths;

- (NSMutableSet *)setFromNodeInclusive:(BOOL)inclusive;
- (NSMutableArray *)arrayFromNodeInclusive:(BOOL)inclusive;

- (void)addChildrenToCollection:(id)collection;
@end
