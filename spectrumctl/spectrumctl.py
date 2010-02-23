#!/usr/bin/python -Wignore::DeprecationWarning
# -*- coding: utf-8 -*-
#
# spectrumctl can be used to control your spectrum-instances. Valid actions are
# start, stop, restart and reload. By default, spectrumctl acts on all instances
# defined in /etc/spectrum/
#
# Copyright (C) 2009, 2010 Mathias Ertl
#
# This file is part of Spectrumctl.
#
# Spectrumctl is free software; you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation; either version 3 of the License, or (at your option) any later
# version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along with
# this program; if not, see <http://www.gnu.org/licenses/>.

import os, sys
from spectrum import *
from optparse import *

description='''spectrumctl can be used to control your spectrum-instances.
Valid actions are start, stop, restart, reload and list. By default, spectrumctl 
acts on all transports defined in /etc/spectrum/'''

parser = OptionParser( usage='Usage: %prog [options] action', version='0.1', description=description)
parser.add_option( '-c', '--config', metavar='FILE',
	help = 'Only act on transport configured in FILE (ignored for list)' )
parser.add_option( '-d', '--config-dir', metavar='DIR', default='/etc/spectrum',
	help = 'Act on all transports configured in DIR (default: %default)' )
parser.add_option( '-q', '--quiet', action='store_true', default=False,
	help = 'Do not print any output (ignored for list)' )

list_group = OptionGroup( parser, 'Options for action "list"' )
list_group.add_option( '--status', choices=['running', 'stopped', 'unknown'],
	help='Only show transports with given status. Valid values are "running", "stopped" and "unknown"' )
parser.add_option_group( list_group )

start_group = OptionGroup( parser, 'Options for action "start"' )
start_group.add_option( '--su', default='spectrum',
	help = 'Start spectrum as this user (default: %default)' )
parser.add_option_group( start_group )

options, args = parser.parse_args()

init_actions = [ 'start', 'stop', 'restart', 'reload', 'status' ]
complex_actions = [ 'list' ]
all_actions = init_actions + complex_actions

if len( args ) != 1:
	print( "Error: Please give exactly one action." )
	sys.exit(1)

action = args[0]
if action not in all_actions:
	print( "Unknown action." )
	sys.exit(1)

def log( msg, newline=True ):
	if not options.quiet or action == "list":
		if newline:
			print( msg )
		else:
			print( msg ),
#			print( msg, end='' ) #python 3
	
def act( instance ):
	if not instance.enabled():
		if not options.quiet:
			print( "%s is disabled in config-file." %(instance.get_jid()) )
		return 0

	log( "%s %s..."%(action.title(), instance.get_jid()), False )
	exit, string = getattr( instance, action )()
	log( string )
	return exit

if options.config:
	instance = spectrum.spectrum( options, options.config )

	if action in init_actions:
		ret = act( instance )
		sys.exit( ret )
	else:
		ret = getattr( actions, action )( [instance] )
else:
	if not os.path.exists( options.config_dir ):
		log( "Error: %s: No such directory"%(options.config_dir) )
		sys.exit(1)

	ret = 0
	config_list = os.listdir( options.config_dir )
	instances = []
	for file in config_list:
		path = '%s/%s'%(options.config_dir, file)
		instances.append( spectrum.spectrum( options, path ) )

	if action in init_actions:
		for instance in instances:
			ret += act( instance )
	else:
		ret = getattr( actions, action )( instances )

	if ret != 0:
		log( "Warning: Some actions failed." )
		sys.exit( ret )