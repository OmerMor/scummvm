/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef STARTREK_TEXT_H
#define STARTREK_TEXT_H


namespace StarTrek {

// The type to use for text references (values of "GameStringIDs" enum).
// NOTE: if this typedef is changed, certain lines in "saveload.cpp" would also need to be
// changed. Better to leave this as-is.
typedef int32 TextRef;

// Text that's loaded from "GROUND.TXT". First 0x40 pieces of text are for items.
// TODO: Floppy version has different numbers for this.
enum GroundTextIDs {
	// Generic "perform undefined action" text (ie. look at nothing, talk to wall)
	GROUNDTX_LOOK_KIRK = 0x49,
	GROUNDTX_LOOK_SPOCK = 0x4a,
	GROUNDTX_LOOK_MCCOY = 0x4b,
	GROUNDTX_LOOK_REDSHIRT = 0x4c,
	GROUNDTX_LOOK_ANYWHERE = 0x4d,
	GROUNDTX_TALK_TO_CREWMAN = 0x4e,
	GROUNDTX_NO_RESPONSE = 0x4f,

	GROUNDTX_KIRK_USE = 0x50,
	GROUNDTX_SPOCK_USE = 0x51,
	GROUNDTX_MCCOY_USE = 0x52,
	GROUNDTX_REDSHIRT_USE = 0x53,
	GROUNDTX_SPOCK_SCAN = 0x54,
	GROUNDTX_MCCOY_SCAN = 0x55,
	GROUNDTX_USE_MEDKIT = 0x56,

	GROUNDTX_PHASER_ON_MCCOY = 0x57, // 8 variations
	GROUNDTX_PHASER_ON_SPOCK = 0x5f, // 8 variations
	GROUNDTX_PHASER_ON_REDSHIRT = 0x67, // 8 variations
	GROUNDTX_PHASER_ANYWHERE = 0x6f, // 7 variations

	GROUNDTX_USE_COMMUNICATOR = 0x76,
	GROUNDTX_NOTHING_HAPPENS = 0x77,
	GROUNDTX_FAIL_TO_OBTAIN_ANYTHING = 0x78
};

// Text that's hardcoded into "RDF" files, and copied into here for a sane referencing
// scheme.
enum GameStringIDs {
	TX_BLANK = -1,
	TX_NULL = 0,
	TX_BLANK_OLD = 1,	// unused, kept as filler
	TX_DIALOG_ERROR,
	TX_ANIMATION_ERROR,

	TX_SPEAKER_KIRK,
	TX_SPEAKER_SPOCK,
	TX_SPEAKER_MCCOY,
	TX_SPEAKER_UHURA,
	TX_SPEAKER_SCOTT,
	TX_SPEAKER_SULU,
	TX_SPEAKER_CHEKOV,

	TX_SPEAKER_EVERTS,
	TX_SPEAKER_ANGIVEN,
	TX_SPEAKER_SIGN,
	TX_SPEAKER_KLINGON,
	TX_SPEAKER_KANDREY,
	TX_SPEAKER_STEPHEN,
	TX_SPEAKER_CHUB,
	TX_SPEAKER_ROBERTS,
	TX_SPEAKER_GRISNASH,
	TX_SPEAKER_NAUIAN,
	TX_SPEAKER_SHIPS_COMPUTER,

	TX_SPEAKER_CHRISTENSEN,
	TX_SPEAKER_SIMPSON,
	TX_SPEAKER_ELASI_GUARD,
	TX_SPEAKER_ELASI_CLANSMAN,
	TX_SPEAKER_ELASI_CERETH,
	TX_SPEAKER_MASADA_CREWMAN,

	TX_SPEAKER_FERRIS,
	TX_SPEAKER_COMPUTER,
	TX_SPEAKER_MARCUS,
	TX_SPEAKER_CHEEVER,
	TX_SPEAKER_PREAX,

	TX_SPEAKER_BUCHERT,
	TX_SPEAKER_MUDD,

	TX_SPEAKER_STRAGEY,
	TX_SPEAKER_QUETZECOATL,
	TX_SPEAKER_TLAOXAC,

	TX_SPEAKER_BENNIE,
	TX_SPEAKER_VLICT,
	TX_SPEAKER_KLINGON_GUARD,
	TX_SPEAKER_ENTITY,
	TX_SPEAKER_BIALBI,
	TX_SPEAKER_VOICE,
	TX_SPEAKER_LIGHT_OF_WAR,
	TX_SPEAKER_LIGHT_OF_KNOWLEDGE,
	TX_SPEAKER_LIGHT_OF_TRAVEL,

	TX_SPEAKER_MOSHER,

	TX_SPEAKER_KIJE,
	TX_SPEAKER_PATTERSON,
	TX_SPEAKER_ANDRADE,
	TX_SPEAKER_ELASI_CAPTAIN,
	TX_SPEAKER_ELASI_WEAPONS_MASTER,
	TX_SPEAKER_ELASI_CREWMAN,
	TX_SPEAKER_BRITTANY_MARATA,

	TX_BRIDU146,

	TX_G_014,
	TX_G_024,
	TX_G_043,

	TX_GENER004,

	TX_COMPA180,
	TX_COMPA185,
	TX_COMPA186,
	TX_COMPA187,
	TX_COMPA189,
	TX_COMPA190,
	TX_COMPA191,
	TX_COMPA193,
	TX_COMPU181,
	TX_COMPU182,
	TX_COMPU186,
	TX_COMPU187,
	TX_COMPU188,
	TX_COMPU189,
	TX_COMPU190,
	TX_COMPU192,
	TX_COMPU193,

	TX_DEM0N009,	// kept because it's also used as an enhancement in mudd1
	TX_DEM0C001,	// "C" = "Custom" (no ID originally assigned)

	TX_DEM1_F23,

	TX_DEM3_019,	// kept because it's also used as an enhancement in venga

	TX_DEM3_A32,
	TX_DEM3_B32,	// unused?
	TX_DEM3_F21,

	TX_TUG0_F30,
	TX_TUG0_F31,
	TX_TUG0_S06,
	TX_TUG0_S11,

	TX_TUG1_011,

	TX_TUG2_004,
	TX_TUG2_007,
	TX_TUG2_010,
	TX_TUG2_011,
	TX_TUG2_015,
	TX_TUG2_016,
	TX_TUG2_019,
	TX_TUG2J000,
	TX_TUG2J001,
	TX_TUG2J002,
	TX_TUG2J003,
	TX_TUG2C001, // Custom

	TX_TUG3_F27,
	TX_TUG3_S07,
	TX_TUG3_S08,

	TX_LOV0_001,
	TX_LOV0_002,
	TX_LOV0_003,
	TX_LOV0_004,
	TX_LOV0_005,
	TX_LOV0_006,
	TX_LOV0_007,
	TX_LOV0_008,
	TX_LOV0_009,
	TX_LOV0_010,
	TX_LOV0_011,
	TX_LOV0_012,
	TX_LOV0_013,
	TX_LOV0_014,
	TX_LOV0_015,
	TX_LOV0_016,
	TX_LOV0_017,
	TX_LOV0_019,
	TX_LOV0_020,
	TX_LOV0_021,
	TX_LOV0_022,
	TX_LOV0_023,
	TX_LOV0_024,
	TX_LOV0_025,
	TX_LOV0_026,
	TX_LOV0_027,
	TX_LOV0_028,
	TX_LOV0_029,
	TX_LOV0_030,
	TX_LOV0_031,
	TX_LOV0_033,
	TX_LOV0_035,
	TX_LOV0_036,
	TX_LOV0_037,
	TX_LOV0_038,
	TX_LOV0_039,
	TX_LOV0_040,
	TX_LOV0_041,
	TX_LOV0_042,
	TX_LOV0_043,
	TX_LOV0_045,
	TX_LOV0_046,
	TX_LOV0_047,
	TX_LOV0_048,
	TX_LOV0_049,
	TX_LOV0_050,
	TX_LOV0_101,
	TX_LOV0_102,
	TX_LOV0_103,
	TX_LOV0_104,
	TX_LOV0_105,
	TX_LOV0_106,
	TX_LOV0_107,
	TX_LOV0_124,
	TX_LOV0N000,
	TX_LOV0N001,
	TX_LOV0N002,
	TX_LOV0N003,
	TX_LOV0N004,
	TX_LOV0N005,
	TX_LOV0N006,
	TX_LOV0N007,
	TX_LOV0N008,
	TX_LOV0N009,


	TX_LOV1_001,
	TX_LOV1_002,
	TX_LOV1_003,
	TX_LOV1_004,
	TX_LOV1_005,
	TX_LOV1_006,
	TX_LOV1_007,
	TX_LOV1_008,
	TX_LOV1_009,
	TX_LOV1_010,
	TX_LOV1_011,
	TX_LOV1_012,
	TX_LOV1_013,
	TX_LOV1_014,
	TX_LOV1_015,
	TX_LOV1_016,
	TX_LOV1_017,
	TX_LOV1_018,
	TX_LOV1_019,
	TX_LOV1_021,
	TX_LOV1_022,
	TX_LOV1_023,
	TX_LOV1_024,
	TX_LOV1_025,
	TX_LOV1_026,
	TX_LOV1_027,
	TX_LOV1_028,
	TX_LOV1N000,
	TX_LOV1N001,
	TX_LOV1N002,
	TX_LOV1N003,
	TX_LOV1N004,
	TX_LOV1N005,
	TX_LOV1N006,
	TX_LOV1N007,
	TX_LOV1N008,
	TX_LOV1N009,
	TX_LOV1N010,
	TX_LOV1N011,
	TX_LOV1N012,
	TX_LOV1N013,
	TX_LOV1N014,
	TX_LOV1N015,
	TX_LOV1N016,
	TX_LOV1N017,
	TX_LOV1N018,
	TX_LOV1N019,
	TX_LOV1N020,
	TX_LOV1N021,
	TX_LOV1N022,
	TX_LOV1N023,
	TX_LOV1N034,
	TX_LOV1N035,


	TX_LOV2_001,
	TX_LOV2_002,
	TX_LOV2_003,
	TX_LOV2_004,
	TX_LOV2_005,
	TX_LOV2_006,
	TX_LOV2_007,
	TX_LOV2_008,
	TX_LOV2_009,
	TX_LOV2_010,
	TX_LOV2_011,
	TX_LOV2_012,
	TX_LOV2_014,
	TX_LOV2_015,
	TX_LOV2_016,
	TX_LOV2_017,
	TX_LOV2_018,
	TX_LOV2_019,
	TX_LOV2_020,
	TX_LOV2_021,
	TX_LOV2_022,
	TX_LOV2_023,
	TX_LOV2_024,
	TX_LOV2_025,
	TX_LOV2_026,
	TX_LOV2_027,
	TX_LOV2_028,
	TX_LOV2_029,
	TX_LOV2_030,
	TX_LOV2_031,
	TX_LOV2_032,
	TX_LOV2_033,
	TX_LOV2_034,
	TX_LOV2_035,
	TX_LOV2_036,
	TX_LOV2_037,
	TX_LOV2_038,
	TX_LOV2_039,
	TX_LOV2_040,
	TX_LOV2_041,
	TX_LOV2_043,
	TX_LOV2N000,
	TX_LOV2N001,
	TX_LOV2N002,
	TX_LOV2N003,
	TX_LOV2N004,
	TX_LOV2N005,
	TX_LOV2N006,
	TX_LOV2N007,
	TX_LOV2N008,
	TX_LOV2N009,
	TX_LOV2N010,
	TX_LOV2N011,
	TX_LOV2N012,
	TX_LOV2N013,
	TX_LOV2N014,
	TX_LOV2N015,
	TX_LOV2N016,
	TX_LOV2N017,
	TX_LOV2N018,
	TX_LOV2N019,
	TX_LOV2N024,
	TX_LOV2N025,
	TX_LOV2N026,
	TX_LOV2N027,
	TX_LOV2N028,
	TX_LOV2N029,
	TX_LOV2N030,
	TX_LOV2N031,
	TX_LOV2N033,
	TX_LOV2N034,
	TX_LOV2N035,
	TX_LOV2N036,
	TX_LOV2N037,
	TX_LOV2N038,
	TX_LOV2N039,
	TX_LOV2N040,
	TX_LOV2N041,
	TX_LOV2N042,
	TX_LOV2N043,
	TX_LOV2N044,
	TX_LOV2N045,
	TX_LOV2N046,
	TX_LOV2N047,
	TX_LOV2N048,
	TX_LOV2N049,
	TX_LOV2N050,
	TX_LOV2N051,


	TX_LOV3_001,
	TX_LOV3_002,
	TX_LOV3_003,
	TX_LOV3_004,
	TX_LOV3_005,
	TX_LOV3_006,
	TX_LOV3_007,
	TX_LOV3_008,
	TX_LOV3_009,
	TX_LOV3_010,
	TX_LOV3_011,
	TX_LOV3_012,
	TX_LOV3_013,
	TX_LOV3_014,
	TX_LOV3_015,
	TX_LOV3_016,
	TX_LOV3_017,
	TX_LOV3_018,
	TX_LOV3_019,
	TX_LOV3_020,
	TX_LOV3_021,
	TX_LOV3_022,
	TX_LOV3_023,
	TX_LOV3_024,
	TX_LOV3_025,
	TX_LOV3_026,
	TX_LOV3N000,
	TX_LOV3N001,
	TX_LOV3N002,
	TX_LOV3N003,
	TX_LOV3N004,
	TX_LOV3N005,
	TX_LOV3N006,
	TX_LOV3N007,
	TX_LOV3N008,
	TX_LOV3N009,
	TX_LOV3N010,
	TX_LOV3N011,
	TX_LOV3N012,
	TX_LOV3N013,
	TX_LOV3N014,
	TX_LOV3N015,
	TX_LOV3N016,
	TX_LOV3N017,
	TX_LOV3N018,
	TX_LOV3N019,
	TX_LOV3N020,
	TX_LOV3N021,
	TX_LOV3N022,
	TX_LOV3N023,
	TX_LOV3N024,
	TX_LOV3N025,
	TX_LOV3N026,
	TX_LOV3N027,
	TX_LOV3N028,
	TX_LOV3N029,
	TX_LOV3N030,
	TX_LOV3N031,
	TX_LOV3N032,
	TX_LOV3NA08,
	TX_LOV3NA09,
	TX_LOV3NA20,
	TX_LOV3NA21,
	TX_LOV3NA22,
	TX_LOV3NA23,
	TX_LOV3NJ32,


	TX_LOV4_001,
	TX_LOV4_002,
	TX_LOV4_003,
	TX_LOV4_004,
	TX_LOV4_005,
	TX_LOV4_006,
	TX_LOV4_007,
	TX_LOV4_009,
	TX_LOV4_010,
	TX_LOV4_011,
	TX_LOV4_012,
	TX_LOV4_013,
	TX_LOV4_014,
	TX_LOV4_015,
	TX_LOV4_016,
	TX_LOV4_017,
	TX_LOV4_018,
	TX_LOV4_019,
	TX_LOV4_020,
	TX_LOV4_021,
	TX_LOV4_022,
	TX_LOV4_023,
	TX_LOV4_024,
	TX_LOV4_025,
	TX_LOV4_026,
	TX_LOV4_027,
	TX_LOV4_028,
	TX_LOV4_029,
	TX_LOV4N000,
	TX_LOV4N001,
	TX_LOV4N002,
	TX_LOV4N003,
	TX_LOV4N004,
	TX_LOV4N005,
	TX_LOV4N006,
	TX_LOV4N007,
	TX_LOV4N008,
	TX_LOV4N009,
	TX_LOV4N010,
	TX_LOV4N011,
	TX_LOV4N012,
	TX_LOV4N013,


	TX_LOV5_001,
	TX_LOV5_002,
	TX_LOV5_003,
	TX_LOV5_004,
	TX_LOV5_005,
	TX_LOV5_006,
	TX_LOV5_007,
	TX_LOV5_008,
	TX_LOV5_009,
	TX_LOV5_010,
	TX_LOV5_011,
	TX_LOV5_013,
	TX_LOV5_014,
	TX_LOV5_015,
	TX_LOV5_016,
	TX_LOV5_017,
	TX_LOV5_018,
	TX_LOV5_019,
	TX_LOV5_020,
	TX_LOV5_021,
	TX_LOV5_023,
	TX_LOV5_024,
	TX_LOV5_025,
	TX_LOV5_026,
	TX_LOV5_027,
	TX_LOV5_028,
	TX_LOV5_029,
	TX_LOV5_030,
	TX_LOV5_031,
	TX_LOV5_032,
	TX_LOV5_033,
	TX_LOV5_034,
	TX_LOV5_036,
	TX_LOV5_038,
	TX_LOV5_039,
	TX_LOV5_040,
	TX_LOV5_041,
	TX_LOV5_042,
	TX_LOV5_043,
	TX_LOV5_044,
	TX_LOV5_045,
	TX_LOV5_046,
	TX_LOV5_047,
	TX_LOV5_048,
	TX_LOV5_049,
	TX_LOV5_050,
	TX_LOV5_051,
	TX_LOV5_052,
	TX_LOV5_053,
	TX_LOV5_054,
	TX_LOV5_055,
	TX_LOV5_056,
	TX_LOV5_057,
	TX_LOV5_058,
	TX_LOV5_059,
	TX_LOV5_060,
	TX_LOV5_061,
	TX_LOV5N000,
	TX_LOV5N001,
	TX_LOV5N002,
	TX_LOV5N003,
	TX_LOV5N004,
	TX_LOV5N005,
	TX_LOV5N006,
	TX_LOV5N007,
	TX_LOV5N008,
	TX_LOV5N009,
	TX_LOV5N010,
	TX_LOV5N011,
	TX_LOV5N012,
	TX_LOV5N013,
	TX_LOV5N014,
	TX_LOV5N015,
	TX_LOV5N016,
	TX_LOV5N017,
	TX_LOV5N018,
	TX_LOV5C001, // Custom


	TX_LOVA_100,
	TX_LOVA_F01,
	TX_LOVA_F02,
	TX_LOVA_F03,
	TX_LOVA_F04,
	TX_LOVA_F07,
	TX_LOVA_F08,
	TX_LOVA_F10,
	TX_LOVA_F54,
	TX_LOVA_F55,


	TX_MUD0_001,
	TX_MUD0_002,
	TX_MUD0_003,
	TX_MUD0_004,
	TX_MUD0_005,
	TX_MUD0_006,
	TX_MUD0_007,
	TX_MUD0_008,
	TX_MUD0_009,
	TX_MUD0_010,
	TX_MUD0_011,
	TX_MUD0_012,
	TX_MUD0_013,
	TX_MUD0_014,
	TX_MUD0_015,
	TX_MUD0_016,
	TX_MUD0_017,
	TX_MUD0_018,
	TX_MUD0_019,
	TX_MUD0_020,
	TX_MUD0_021,
	TX_MUD0_022,
	TX_MUD0_023,
	TX_MUD0_024,
	TX_MUD0_025,
	TX_MUD0_026,
	TX_MUD0_027,
	TX_MUD0_028,
	TX_MUD0_029,
	TX_MUD0_030,
	TX_MUD0_031,
	TX_MUD0_032,
	TX_MUD0_033,
	TX_MUD0_034,
	TX_MUD0_035,
	TX_MUD0_036,
	TX_MUD0_037,
	TX_MUD0_038,
	TX_MUD0_039,
	TX_MUD0_040,
	TX_MUD0_041,
	TX_MUD0N000,
	TX_MUD0N001,
	TX_MUD0N002,
	TX_MUD0N003,
	TX_MUD0N004,
	TX_MUD0N005,
	TX_MUD0N006,
	TX_MUD0N007,
	TX_MUD0N008,
	TX_MUD0N009,
	TX_MUD0N010,
	TX_MUD0N011,
	TX_MUD0N012,
	TX_MUD0N013,
	TX_MUD0N014,
	TX_MUD0N015,
	TX_MUD0N016,
	TX_MUD0N017,
	// UNUSED
	TX_MUD0N019,


	TX_MUD1_001,
	TX_MUD1_002,
	TX_MUD1_003,
	TX_MUD1_004,
	TX_MUD1_005,
	TX_MUD1_006,
	TX_MUD1_007,
	TX_MUD1_008,
	TX_MUD1_009,
	TX_MUD1_010,
	TX_MUD1_011,
	TX_MUD1_012,
	TX_MUD1_013,
	TX_MUD1_014,
	TX_MUD1_015,
	TX_MUD1_016,
	TX_MUD1_017,
	// UNUSED
	TX_MUD1_019,
	TX_MUD1_020,
	TX_MUD1_021,
	TX_MUD1_022,
	TX_MUD1_023,
	TX_MUD1_024,
	TX_MUD1_025,
	TX_MUD1_026,
	TX_MUD1_027,
	TX_MUD1_028,
	TX_MUD1N000,
	TX_MUD1N001,
	TX_MUD1N002,
	TX_MUD1N003,
	TX_MUD1N004,
	TX_MUD1N005,
	TX_MUD1N006,
	TX_MUD1N007,
	TX_MUD1N008,
	TX_MUD1N009,
	TX_MUD1N010,
	TX_MUD1N011,
	TX_MUD1N012,
	TX_MUD1N013,
	TX_MUD1N014,
	TX_MUD1N015,
	TX_MUD1N016,


	TX_MUD2_001,
	TX_MUD2_002,
	TX_MUD2_003,
	TX_MUD2_004,
	TX_MUD2_005,
	TX_MUD2_006,
	TX_MUD2_007,
	TX_MUD2_008,
	TX_MUD2_009,
	TX_MUD2_010,
	TX_MUD2_011,
	TX_MUD2_012,
	TX_MUD2_013,
	TX_MUD2_014,
	TX_MUD2_015,
	TX_MUD2_016,
	// UNUSED
	TX_MUD2_018,
	TX_MUD2_019,
	TX_MUD2_020,
	TX_MUD2_021,
	TX_MUD2_022,
	TX_MUD2_023,
	TX_MUD2_024,
	TX_MUD2_025,
	TX_MUD2_026,
	TX_MUD2_027,
	TX_MUD2_028,
	TX_MUD2_029,
	TX_MUD2_030,
	TX_MUD2_031,
	TX_MUD2_032,
	TX_MUD2_033,
	TX_MUD2_034,
	TX_MUD2_035,
	TX_MUD2_036,
	TX_MUD2_037,
	TX_MUD2_038,
	TX_MUD2_039,
	TX_MUD2_040,
	// UNUSED
	TX_MUD2_042,
	TX_MUD2_043,
	TX_MUD2_044,
	TX_MUD2_045,
	TX_MUD2_046,
	TX_MUD2_047,
	TX_MUD2_048,
	TX_MUD2_049,
	TX_MUD2_050,
	TX_MUD2_051,
	TX_MUD2_052,
	TX_MUD2_053,
	TX_MUD2_054,
	TX_MUD2_055,
	TX_MUD2N000,
	TX_MUD2N001,
	TX_MUD2N002,
	TX_MUD2N003,
	TX_MUD2N004,
	TX_MUD2N005,
	TX_MUD2N006,
	TX_MUD2N007,
	TX_MUD2N008,
	TX_MUD2N009,
	TX_MUD2N010,
	TX_MUD2N011,


	// MISSING
	TX_MUD3_002,
	TX_MUD3_003,
	// MISSING
	TX_MUD3_005,
	TX_MUD3_006,
	TX_MUD3_007,
	TX_MUD3_008,
	TX_MUD3_009,
	TX_MUD3_010,
	TX_MUD3_011,
	TX_MUD3_012,
	TX_MUD3_013,
	TX_MUD3_014,
	TX_MUD3_015,
	TX_MUD3_016,
	TX_MUD3_017,
	TX_MUD3_018,
	TX_MUD3_019,
	TX_MUD3_020,
	TX_MUD3_021,
	TX_MUD3_022,
	TX_MUD3_023,
	TX_MUD3_024,
	TX_MUD3_025,
	TX_MUD3_026,
	TX_MUD3_027,
	TX_MUD3_028,
	TX_MUD3_029,
	TX_MUD3_030,
	TX_MUD3_031,
	TX_MUD3_032,
	TX_MUD3_033,
	TX_MUD3_034,
	TX_MUD3_035,
	TX_MUD3_036,
	TX_MUD3_037,
	TX_MUD3_038,
	TX_MUD3_039,
	TX_MUD3_040,
	TX_MUD3_041,
	TX_MUD3_042,
	TX_MUD3_043,
	TX_MUD3_044,
	// UNUSED
	TX_MUD3_046,
	TX_MUD3_047,
	TX_MUD3_048,
	TX_MUD3_049,
	TX_MUD3_050,
	TX_MUD3_051,
	TX_MUD3_052,
	TX_MUD3_053,
	TX_MUD3_054,
	TX_MUD3_055,
	TX_MUD3_056,
	TX_MUD3_057,
	TX_MUD3_058,
	TX_MUD3_059,
	TX_MUD3_060,
	TX_MUD3_061,
	TX_MUD3_062,
	TX_MUD3_063,
	TX_MUD3_064,
	TX_MUD3_065,
	TX_MUD3_066,
	TX_MUD3_067,
	TX_MUD3_068,
	TX_MUD3_069,
	TX_MUD3_070,
	TX_MUD3_071,
	TX_MUD3N000,
	TX_MUD3N001,
	TX_MUD3N002,
	TX_MUD3N003,
	TX_MUD3N004,
	TX_MUD3N005,
	TX_MUD3N006,
	TX_MUD3N007,
	TX_MUD3N008,
	TX_MUD3N009,
	TX_MUD3N010,
	TX_MUD3N011,
	TX_MUD3N012,
	TX_MUD3N013,
	TX_MUD3N014,
	TX_MUD3N015,
	TX_MUD3N016,
	TX_MUD3N017,
	TX_MUD3N018,
	TX_MUD3N019,
	TX_MUD3N020,
	TX_MUD3C001,


	TX_MUD4_001,
	TX_MUD4_002,
	TX_MUD4_003,
	TX_MUD4_004,
	TX_MUD4_005,
	TX_MUD4_006,
	TX_MUD4_007,
	TX_MUD4_008,
	TX_MUD4_009,
	TX_MUD4_010,
	TX_MUD4_011,
	TX_MUD4_012,
	TX_MUD4_013,
	TX_MUD4_014,
	TX_MUD4_015,
	TX_MUD4_016,
	TX_MUD4_017,
	TX_MUD4_018,
	TX_MUD4_019,
	TX_MUD4_020,
	TX_MUD4_021,
	TX_MUD4_022,
	TX_MUD4_023,
	TX_MUD4_024,
	TX_MUD4_025,
	TX_MUD4_026,
	TX_MUD4_027,
	TX_MUD4_028,
	TX_MUD4_029,
	TX_MUD4_030,
	TX_MUD4_031,
	TX_MUD4_032,
	TX_MUD4_033,
	TX_MUD4_034,
	TX_MUD4_035,
	TX_MUD4_036,
	TX_MUD4_037,
	TX_MUD4_038,
	TX_MUD4_039,
	TX_MUD4_040,
	TX_MUD4_041,
	TX_MUD4_042,
	TX_MUD4_043,
	// UNUSED
	TX_MUD4_045,
	TX_MUD4_046,
	TX_MUD4_047,
	TX_MUD4_048,
	TX_MUD4_049,
	TX_MUD4_050,
	TX_MUD4_051,
	TX_MUD4_052,
	TX_MUD4_053,
	TX_MUD4_054,
	TX_MUD4_055,
	TX_MUD4_056,
	TX_MUD4_057,
	TX_MUD4_058,
	TX_MUD4_059,
	TX_MUD4_060,
	TX_MUD4_061,
	TX_MUD4_062,
	TX_MUD4_063,
	TX_MUD4_064,
	TX_MUD4_065,
	TX_MUD4_066,
	TX_MUD4_067,
	TX_MUD4_068,
	TX_MUD4_069,
	TX_MUD4_070,
	TX_MUD4_071,
	TX_MUD4_072,
	TX_MUD4_073,
	TX_MUD4_074,
	TX_MUD4_075,
	TX_MUD4_076,
	TX_MUD4_A29,
	TX_MUD4_S02,
	TX_MUD4_S03,
	TX_MUD4_S04,
	TX_MUD4N000,
	TX_MUD4N001,
	TX_MUD4N002,
	TX_MUD4N003,
	TX_MUD4N004,
	TX_MUD4N005,
	TX_MUD4N006,
	TX_MUD4N007,
	TX_MUD4N008,
	TX_MUD4N009,
	TX_MUD4N011,
	TX_MUD4N012,
	TX_MUD4N013,


	TX_MUD5_001,
	TX_MUD5_002,
	TX_MUD5_003,
	TX_MUD5_004,
	TX_MUD5_005,
	TX_MUD5_006,
	TX_MUD5_007,
	// UNUSED
	TX_MUD5_009,
	TX_MUD5_010,
	TX_MUD5_011,
	TX_MUD5_012,
	TX_MUD5_013,
	TX_MUD5_014,
	TX_MUD5_015,
	TX_MUD5_016,
	TX_MUD5_017,
	TX_MUD5_018,
	TX_MUD5_019,
	TX_MUD5_020,
	TX_MUD5_021,
	TX_MUD5_022,
	TX_MUD5_023,
	TX_MUD5_024,
	TX_MUD5_025,
	TX_MUD5_026,
	TX_MUD5_027,
	TX_MUD5_028,
	// MISSING
	TX_MUD5_030,
	TX_MUD5_031,
	TX_MUD5_032,
	TX_MUD5_033,
	TX_MUD5_034,
	TX_MUD5_035,
	TX_MUD5_036,
	TX_MUD5_037,
	TX_MUD5_038,
	TX_MUD5_039,
	TX_MUD5_040,
	TX_MUD5N000,
	TX_MUD5N001,
	TX_MUD5N002,
	TX_MUD5N003,
	TX_MUD5N004,
	TX_MUD5N005,
	TX_MUD5N006,
	TX_MUD5N007,
	TX_MUD5N008,
	TX_MUD5N009,
	TX_MUD5N010,
	TX_MUD5N011,
	TX_MUD5N012,
	TX_MUD5N105,


	// MISSING
	TX_FEA0_002,
	TX_FEA0_003,
	TX_FEA0_004,
	TX_FEA0_005,
	TX_FEA0_006,
	TX_FEA0_007,
	TX_FEA0_008,
	TX_FEA0_009,
	TX_FEA0_010,
	TX_FEA0_011,
	TX_FEA0_012,
	TX_FEA0_013,
	TX_FEA0_014,
	TX_FEA0_015,
	TX_FEA0_016,
	TX_FEA0_017,
	TX_FEA0_018,
	TX_FEA0_019,
	TX_FEA0_020,
	TX_FEA0_021,
	TX_FEA0_022,
	TX_FEA0_023,
	TX_FEA0_024,
	TX_FEA0_025,
	TX_FEA0_026,
	TX_FEA0_027,
	TX_FEA0_028,
	TX_FEA0_029,
	TX_FEA0_030,
	TX_FEA0_031,
	TX_FEA0_032,
	TX_FEA0_033,
	TX_FEA0_101,
	TX_FEA0_108,
	TX_FEA0N000,
	TX_FEA0N001,
	TX_FEA0N002,
	TX_FEA0N003,
	TX_FEA0N004,
	TX_FEA0N005,
	TX_FEA0N006,
	TX_FEA0N007,
	TX_FEA0N008,
	TX_FEA0N009,


	TX_FEA1_001,
	TX_FEA1_002,
	TX_FEA1_003,
	TX_FEA1_004,
	TX_FEA1_005,
	TX_FEA1_006,
	TX_FEA1_007,
	TX_FEA1_008,
	TX_FEA1_009,
	TX_FEA1_010,
	TX_FEA1_011,
	TX_FEA1_012,
	TX_FEA1_013,
	TX_FEA1_014,
	TX_FEA1_015,
	// MISSING
	TX_FEA1_017,
	TX_FEA1_018,
	TX_FEA1_019,
	TX_FEA1_020, // UNUSED
	TX_FEA1_021,
	TX_FEA1_022, // UNUSED
	TX_FEA1_023,
	TX_FEA1_024,
	TX_FEA1_025,
	TX_FEA1_026,
	TX_FEA1_027,
	TX_FEA1_028,
	TX_FEA1_029,
	TX_FEA1_030,
	TX_FEA1_031,
	TX_FEA1_032,
	TX_FEA1_033,
	TX_FEA1_034,
	TX_FEA1_035,
	// MISSING
	TX_FEA1_037,
	TX_FEA1_038,
	TX_FEA1_039,
	TX_FEA1_040,
	TX_FEA1_041,
	TX_FEA1_042,
	TX_FEA1_043,
	TX_FEA1_044,
	TX_FEA1_045,
	TX_FEA1_046,
	TX_FEA1_047,
	TX_FEA1_048,
	TX_FEA1_049,
	TX_FEA1_050,
	TX_FEA1_051,
	TX_FEA1_052,
	TX_FEA1_053,
	TX_FEA1_054,
	TX_FEA1_055,
	TX_FEA1_056, // UNUSED
	TX_FEA1_057,
	TX_FEA1_A46,
	TX_FEA1_F25,
	TX_FEA1N000,
	TX_FEA1N001,
	TX_FEA1N002,
	TX_FEA1N003,
	TX_FEA1N004,
	TX_FEA1N005,
	TX_FEA1N006,
	TX_FEA1N007, // UNUSED
	TX_FEA1N008,
	TX_FEA1N009,
	TX_FEA1N010,
	TX_FEA1N011,
	TX_FEA1N012,
	TX_FEA1N013,
	TX_FEA1N014,
	TX_FEA1N015,
	TX_FEA1N016,
	TX_FEA1N017,
	TX_FEA1N018, // UNUSED
	TX_FEA1N019,
	TX_FEA1N020,
	TX_FEA1N021,
	TX_FEA1N022,


	TX_FEA2_001,
	TX_FEA2_002,
	TX_FEA2_003,
	TX_FEA2_004,
	TX_FEA2_005,
	TX_FEA2_006,
	TX_FEA2_007,
	TX_FEA2_008,
	TX_FEA2_009,
	TX_FEA2_010,
	TX_FEA2N000,
	TX_FEA2N001,
	TX_FEA2N002,
	TX_FEA2N003,
	TX_FEA2N004,
	TX_FEA2N005,
	TX_FEA2N006,
	TX_FEA2N007,
	TX_FEA2N008,


	TX_FEA3_001,
	TX_FEA3_002,
	TX_FEA3_003,
	TX_FEA3_004,
	TX_FEA3_005,
	TX_FEA3_006,
	TX_FEA3_007,
	TX_FEA3_008,
	TX_FEA3_009,
	TX_FEA3_010,
	TX_FEA3_011,
	TX_FEA3_012,
	TX_FEA3_013,
	TX_FEA3_014,
	TX_FEA3_015,
	TX_FEA3_016,
	TX_FEA3_017,
	TX_FEA3_018,
	TX_FEA3_019,
	TX_FEA3_020,
	TX_FEA3_021,
	TX_FEA3_022,
	TX_FEA3_023,
	TX_FEA3_024,
	TX_FEA3_025,
	TX_FEA3_026,
	TX_FEA3_027,
	TX_FEA3_028,
	TX_FEA3_029,
	TX_FEA3_030,
	TX_FEA3_031,
	TX_FEA3_032,
	TX_FEA3_033,
	TX_FEA3_034,
	TX_FEA3_035,
	TX_FEA3_036,
	TX_FEA3_037,
	TX_FEA3_038,
	TX_FEA3_039,
	TX_FEA3_040,
	TX_FEA3_041,
	TX_FEA3_042,
	TX_FEA3_043,
	TX_FEA3_044,
	TX_FEA3N000,
	TX_FEA3N001,
	TX_FEA3N002,
	TX_FEA3N003,
	TX_FEA3N004,
	TX_FEA3N005,
	TX_FEA3N006,
	TX_FEA3N007,
	// MISSING
	TX_FEA3N010,
	TX_FEA3N011,
	TX_FEA3N012,


	TX_FEA4_001,
	TX_FEA4_002,
	TX_FEA4_003,
	TX_FEA4_004,
	TX_FEA4_005,
	TX_FEA4_006,
	TX_FEA4_007,
	TX_FEA4_008,
	TX_FEA4_009,
	TX_FEA4_010,
	TX_FEA4_011,
	TX_FEA4_012,
	TX_FEA4_013,
	TX_FEA4N000,
	TX_FEA4N001,
	TX_FEA4N002,
	TX_FEA4N003,
	TX_FEA4N004,
	TX_FEA4N005,
	TX_FEA4N006,
	TX_FEA4N007,
	TX_FEA4N008,


	TX_FEA5_001,
	TX_FEA5_002,
	TX_FEA5_003,
	TX_FEA5_004,
	TX_FEA5_005,
	TX_FEA5_006,
	TX_FEA5_007,
	TX_FEA5_008,
	TX_FEA5_009,
	TX_FEA5_010,
	TX_FEA5_011,
	// MISSING
	TX_FEA5_013,
	TX_FEA5_014,
	TX_FEA5_015,
	TX_FEA5_016,
	// MISSING
	TX_FEA5_018,
	TX_FEA5_019,
	TX_FEA5_020,
	TX_FEA5_021, // UNUSED
	TX_FEA5_022,
	TX_FEA5_023,
	TX_FEA5_024,
	TX_FEA5_025,
	TX_FEA5_026,
	TX_FEA5_027,
	TX_FEA5_028,
	TX_FEA5_029,
	TX_FEA5_030,
	TX_FEA5_031,
	TX_FEA5_032,
	TX_FEA5_033,
	TX_FEA5_034,
	TX_FEA5_035,
	TX_FEA5_036,
	TX_FEA5_037,
	TX_FEA5_038,
	TX_FEA5_039,
	TX_FEA5_040,
	TX_FEA5N000,
	TX_FEA5N001,
	TX_FEA5N002,
	TX_FEA5N003,
	TX_FEA5N004,
	TX_FEA5N005,
	TX_FEA5N006,
	TX_FEA5N007,
	TX_FEA5N008,
	TX_FEA5N009,
	TX_FEA5N010,
	TX_FEA5N011,
	TX_FEA5N012,
	TX_FEA5N013,
	TX_FEA5N014,
	TX_FEA5N015,


	TX_FEA6_001,
	TX_FEA6_002,
	TX_FEA6_003,
	TX_FEA6_004,
	TX_FEA6_005,
	TX_FEA6_006,
	TX_FEA6_007,
	TX_FEA6_008,
	TX_FEA6_009,
	// MISSING
	TX_FEA6_011,
	TX_FEA6_012,
	TX_FEA6_013,
	TX_FEA6_014,
	TX_FEA6_015,
	TX_FEA6_016,
	TX_FEA6_017,
	TX_FEA6_018,
	TX_FEA6_019,
	TX_FEA6_020,
	TX_FEA6_021,
	TX_FEA6_022,
	TX_FEA6_023,
	TX_FEA6_024,
	TX_FEA6_025,
	TX_FEA6_026,
	TX_FEA6_027,
	TX_FEA6_028,
	TX_FEA6_029,
	TX_FEA6_030,
	TX_FEA6_031,
	TX_FEA6_032,
	TX_FEA6_033,
	TX_FEA6_034,
	TX_FEA6_035,
	TX_FEA6_036,
	TX_FEA6_037,
	TX_FEA6_038,
	TX_FEA6_039,
	TX_FEA6_040,
	TX_FEA6_041,
	TX_FEA6_042,
	TX_FEA6_043,
	TX_FEA6N000,
	TX_FEA6N001,
	TX_FEA6N002,
	TX_FEA6N003,
	TX_FEA6N004,
	TX_FEA6N005,
	TX_FEA6N006, // UNUSED
	TX_FEA6N007,
	TX_FEA6N008,
	TX_FEA6N009,
	TX_FEA6N010,
	TX_FEA6N011,
	TX_FEA6N012,
	TX_FEA6N013,
	TX_FEA6N014,
	TX_FEA6N015,
	TX_FEA6N016,
	TX_FEA6N017,
	// MISSING
	TX_FEA6N020,
	TX_FEA6N028, // UNUSED
	TX_FEA6N029, // UNUSED


	TX_FEA7_001,
	TX_FEA7_002,
	TX_FEA7_003,
	TX_FEA7_004,
	TX_FEA7_005,
	TX_FEA7_006,
	TX_FEA7_007,
	TX_FEA7_008,
	TX_FEA7_009,
	TX_FEA7_010,
	TX_FEA7_011,
	TX_FEA7_012,
	TX_FEA7_013,
	TX_FEA7_014,
	TX_FEA7_015,
	TX_FEA7_016,
	TX_FEA7_017,
	TX_FEA7_018,
	TX_FEA7_019,
	TX_FEA7_020,
	TX_FEA7_021,
	TX_FEA7_022,
	TX_FEA7_023,
	TX_FEA7_024,
	TX_FEA7_025,
	TX_FEA7_026,
	TX_FEA7_027,
	TX_FEA7_028,
	TX_FEA7_029,
	TX_FEA7_030,


	TX_TRI0_001,
	TX_TRI0_002,
	TX_TRI0_003,
	TX_TRI0_004,
	// MISSING
	TX_TRI0_006,
	TX_TRI0_007,
	TX_TRI0_008,
	TX_TRI0_009,
	TX_TRI0_010,
	TX_TRI0_011,
	// UNUSED
	TX_TRI0_013,
	TX_TRI0_014,
	TX_TRI0_015,
	TX_TRI0_016,
	TX_TRI0_017,
	TX_TRI0_018,
	TX_TRI0_019,
	TX_TRI0_020,
	TX_TRI0_021,
	TX_TRI0_022,
	TX_TRI0_023,
	TX_TRI0_024,
	TX_TRI0_025,
	TX_TRI0_026,
	TX_TRI0_027,
	TX_TRI0_028,
	TX_TRI0_029,
	TX_TRI0_030,
	TX_TRI0_031,
	// UNUSED
	TX_TRI0_034,
	TX_TRI0_035,
	TX_TRI0_036,
	TX_TRI0_037,
	TX_TRI0_038,
	TX_TRI0_039,
	TX_TRI0_040,
	TX_TRI0_041,
	TX_TRI0_042,
	TX_TRI0_043,
	TX_TRI0_044,
	TX_TRI0_045,
	TX_TRI0_046,
	TX_TRI0_047,
	TX_TRI0_048,
	TX_TRI0_049,
	TX_TRI0_050,
	TX_TRI0_051,
	TX_TRI0_052,
	TX_TRI0_053,
	TX_TRI0_054,
	TX_TRI0_055,
	TX_TRI0_056,
	TX_TRI0_057,
	TX_TRI0_058,
	TX_TRI0_059,
	TX_TRI0_060,
	TX_TRI0_061,
	TX_TRI0_062,
	TX_TRI0_063,
	TX_TRI0_064,
	TX_TRI0_065,
	TX_TRI0_066,
	// UNUSED (067)
	TX_TRI0_F24,
	TX_TRI0N000,
	TX_TRI0N001,
	TX_TRI0N002,
	TX_TRI0N003,
	TX_TRI0N004,
	TX_TRI0N005,
	TX_TRI0N006,
	TX_TRI0N007,
	TX_TRI0N008,
	TX_TRI0N009,
	TX_TRI0U075,


	// UNUSED (001)
	TX_TRI1_002,
	TX_TRI1_003,
	TX_TRI1_004,
	TX_TRI1_005,
	TX_TRI1_006,
	TX_TRI1_007,
	TX_TRI1_008,
	TX_TRI1_009,
	TX_TRI1_010,
	TX_TRI1_011,
	TX_TRI1_012,
	TX_TRI1_013,
	TX_TRI1_014,
	TX_TRI1_015,
	TX_TRI1_016,
	TX_TRI1_017,
	TX_TRI1_018,
	TX_TRI1_019,
	TX_TRI1_020,
	TX_TRI1_021,
	TX_TRI1_022,
	TX_TRI1_023,
	TX_TRI1_024,
	TX_TRI1_025,
	TX_TRI1_026,
	TX_TRI1_027,
	// UNUSED
	TX_TRI1_029,
	TX_TRI1_030, // UNUSED
	TX_TRI1_031,
	TX_TRI1_032,
	TX_TRI1_033,
	TX_TRI1_034,
	TX_TRI1_035,
	TX_TRI1_036,
	TX_TRI1_037,
	TX_TRI1_038,
	TX_TRI1_039,
	TX_TRI1_040,
	TX_TRI1_041,
	TX_TRI1_042,
	TX_TRI1_043,
	TX_TRI1_044,
	TX_TRI1_045,
	TX_TRI1_046,
	TX_TRI1_047,
	TX_TRI1_048,
	TX_TRI1_049,
	TX_TRI1_050,
	TX_TRI1_051,
	TX_TRI1_052,
	TX_TRI1_053,
	TX_TRI1_054,
	TX_TRI1_055,
	TX_TRI1_056,
	TX_TRI1_057,
	// UNUSED (058 -> 066)
	TX_TRI1_J00,
	TX_TRI1N000,
	TX_TRI1N001,
	TX_TRI1N002,
	TX_TRI1N003,
	TX_TRI1N004,
	TX_TRI1N005,
	TX_TRI1N006,
	TX_TRI1N007,
	TX_TRI1N008,
	TX_TRI1N009,
	// UNUSED
	TX_TRI1N011,
	TX_TRI1N012,
	TX_TRI1N013,
	TX_TRI1N014,
	TX_TRI1N015,
	TX_TRI1N016,
	TX_TRI1N017,
	// UNUSED (018 -> 019)
	TX_TRI1U068,
	TX_TRI1U079,
	TX_TRI1U080,
	TX_TRI1U086,
	TX_TRI1U090,
	TX_TRI1U095,
	TX_TRI1U098,
	TX_TRI1U101,
	TX_TRI1U102,
	TX_TRI1U106,
	// UNUSED: TRI1UO68 (that's 'O', not '0'); same as TRI1U068 but before the voice
	// filter on the communicator is applied?
	// There are also TRI3 audio files in the TRI1 folder?
	TX_TRI1C001, // Custom
	TX_TRI1C002,


	TX_QUIET,
	TX_TRI2_001,
	TX_TRI2_002,
	TX_TRI2_003,
	TX_TRI2_004,
	TX_TRI2_005,
	TX_TRI2_006,
	TX_TRI2_007,
	TX_TRI2_008,
	TX_TRI2_009,
	TX_TRI2_010,
	TX_TRI2_011,
	TX_TRI2_012,
	TX_TRI2_013,
	TX_TRI2_014,
	TX_TRI2_015,
	TX_TRI2_016,
	TX_TRI2_017,
	TX_TRI2_018,
	TX_TRI2_019,
	TX_TRI2_020,
	TX_TRI2_021,
	TX_TRI2_022,
	TX_TRI2_023,
	TX_TRI2_024,
	TX_TRI2_025,
	TX_TRI2_026,
	TX_TRI2_027,
	TX_TRI2_028,
	TX_TRI2_029,
	TX_TRI2_030,
	TX_TRI2_031,
	TX_TRI2_032,
	TX_TRI2_033,
	TX_TRI2_034,
	// UNUSED (035 -> 039; voice substitute for Uhura)
	TX_TRI2_F11, // UNUSED
	TX_TRI2N000,
	TX_TRI2N001,
	TX_TRI2N002,
	TX_TRI2N003,
	TX_TRI2N004,
	TX_TRI2N005,
	TX_TRI2N006,
	TX_TRI2N007,
	TX_TRI2N008,
	TX_TRI2U074,
	TX_TRI2U081,
	TX_TRI2U087,
	TX_TRI2U091,
	TX_TRI2U104,


	TX_TRI3_001,
	TX_TRI3_002,
	TX_TRI3_003,
	TX_TRI3_004,
	TX_TRI3_005,
	TX_TRI3_006,
	TX_TRI3_007,
	TX_TRI3_008,
	TX_TRI3_009,
	TX_TRI3_010,
	TX_TRI3_011,
	TX_TRI3_012,
	TX_TRI3_013,
	TX_TRI3_014,
	TX_TRI3_015,
	TX_TRI3_016,
	TX_TRI3_017,
	TX_TRI3_018,
	TX_TRI3_019,
	TX_TRI3_020,
	TX_TRI3_021,
	TX_TRI3_022,
	TX_TRI3_023,
	TX_TRI3_024,
	TX_TRI3_025,
	TX_TRI3_026,
	TX_TRI3_027,
	TX_TRI3_028,
	TX_TRI3_029,
	TX_TRI3_030,
	// UNUSED (031 -> 036; voice substitute for Uhura)
	TX_TRI3_103,
	TX_TRI3_104,
	TX_TRI3_107,
	TX_TRI3N000,
	TX_TRI3N001,
	TX_TRI3N002,
	TX_TRI3N003,
	TX_TRI3N004,
	TX_TRI3N005,
	TX_TRI3N006,
	TX_TRI3N007,
	TX_TRI3U067,
	TX_TRI3U080,
	// UNUSED (U081)
	TX_TRI3U084,
	TX_TRI3U089,
	// UNUSED (U090)
	TX_TRI3U099,


	TX_TRI4_001,
	TX_TRI4_002,
	TX_TRI4_003,
	TX_TRI4_004,
	TX_TRI4_005,
	TX_TRI4_006,
	TX_TRI4_007,
	TX_TRI4_008,
	TX_TRI4_009,
	TX_TRI4_010,
	TX_TRI4_011,
	TX_TRI4_012,
	TX_TRI4_013,
	TX_TRI4_014,
	TX_TRI4_015,
	TX_TRI4_016,
	TX_TRI4_017,
	TX_TRI4_018,
	TX_TRI4_019,
	TX_TRI4_020,
	TX_TRI4_021,
	TX_TRI4_022,
	TX_TRI4_023,
	TX_TRI4_024,
	TX_TRI4_025,
	TX_TRI4_026,
	TX_TRI4_027,
	TX_TRI4_028,
	TX_TRI4_029,
	TX_TRI4_030,
	TX_TRI4_031,
	TX_TRI4_032,
	TX_TRI4_033,
	TX_TRI4_034,
	// UNUSED (035)
	TX_TRI4_036,
	TX_TRI4_037,
	TX_TRI4_038,
	TX_TRI4_039,
	TX_TRI4_040,
	TX_TRI4_041,
	TX_TRI4_042,
	TX_TRI4_043,
	TX_TRI4_044,
	TX_TRI4_045,
	TX_TRI4_046,
	TX_TRI4_047,
	TX_TRI4_048,
	TX_TRI4_049,
	TX_TRI4_050,
	TX_TRI4_051,
	TX_TRI4_052,
	TX_TRI4_053,
	TX_TRI4_054,
	TX_TRI4_055,
	TX_TRI4_056,
	TX_TRI4_057,
	TX_TRI4_058,
	TX_TRI4_059,
	TX_TRI4_060,
	TX_TRI4_061,
	TX_TRI4_062,
	TX_TRI4_063,
	TX_TRI4_064,
	TX_TRI4_065,
	TX_TRI4_066,
	TX_TRI4_067,
	TX_TRI4_068,
	TX_TRI4_069,
	TX_TRI4_070,
	TX_TRI4_071,
	TX_TRI4_072,
	TX_TRI4_073,
	TX_TRI4_074,
	TX_TRI4_075,
	TX_TRI4_076,


	TX_TRI5_001,
	TX_TRI5_002,
	TX_TRI5_003,
	TX_TRI5_004,
	TX_TRI5_005,
	TX_TRI5_006,
	TX_TRI5_007,
	TX_TRI5_008,
	TX_TRI5_009,
	TX_TRI5_010,
	TX_TRI5_011,
	TX_TRI5_012,
	TX_TRI5_013,
	TX_TRI5_014,
	TX_TRI5_015,
	TX_TRI5_016,
	TX_TRI5_017,
	TX_TRI5_018,
	TX_TRI5_019,
	TX_TRI5_020,
	TX_TRI5_021,
	TX_TRI5_022,
	TX_TRI5_023,
	TX_TRI5_024,
	TX_TRI5_025,
	TX_TRI5_026,
	TX_TRI5_027,
	TX_TRI5_028,
	TX_TRI5_029,
	TX_TRI5_030,
	TX_TRI5_031,
	TX_TRI5_032,
	TX_TRI5_033,
	TX_TRI5_034,
	TX_TRI5_035,
	TX_TRI5_036,
	TX_TRI5_037,
	TX_TRI5_038,
	TX_TRI5_039,
	TX_TRI5_040,
	TX_TRI5_041,
	TX_TRI5_042,
	TX_TRI5_043,
	TX_TRI5_044,
	TX_TRI5_045,
	TX_TRI5_046,
	TX_TRI5_047,
	TX_TRI5_048,
	TX_TRI5_049,
	TX_TRI5_050,
	TX_TRI5_051,
	TX_TRI5_052,
	// UNUSED (000 -> 001)
	TX_TRI5N002,
	// UNUSED (003)
	TX_TRI5N004,
	TX_TRI5N005,
	TX_TRI5N006,
	TX_TRI5N007,
	TX_TRI5N008,
	TX_TRI5N009,
	TX_TRI5N010,
	TX_TRI5N011,
	TX_TRI5N012,
	TX_TRI5N013,
	TX_TRI5N014,
	TX_TRI5N015,
	TX_TRI5N016,
	TX_TRI5N017,
	TX_TRI5N018,
	TX_TRI5N019,
	TX_TRI5N020,
	TX_TRI5N021,


	TX_SIN0_001,
	TX_SIN0_002,
	TX_SIN0_003,
	TX_SIN0_004,
	TX_SIN0_005,
	TX_SIN0_006,
	TX_SIN0_007,
	TX_SIN0_008,
	TX_SIN0_009,
	TX_SIN0_010,
	TX_SIN0_011,
	TX_SIN0_012,
	TX_SIN0_013,
	TX_SIN0_014,
	TX_SIN0_015,
	TX_SIN0_016,
	TX_SIN0_017,
	TX_SIN0_018,
	TX_SIN0_019,
	TX_SIN0_020,
	TX_SIN0_021,
	TX_SIN0_022,
	TX_SIN0_023,
	TX_SIN0_024,
	TX_SIN0_025,
	TX_SIN0_026,
	TX_SIN0_027,
	TX_SIN0_028,
	// UNUSED: 029 -> 030
	TX_SIN0_S01,
	TX_SIN0_S48,
	TX_SIN0_S49,
	TX_SIN0_S50,
	TX_SIN0N000,
	TX_SIN0N001,
	TX_SIN0N002,
	TX_SIN0N003,
	TX_SIN0N004,
	TX_SIN0N005,
	TX_SIN0N006,
	TX_SIN0N007,
	TX_SIN0N008,
	TX_SIN0N009,
	TX_SIN0N010,
	TX_SIN0N011,
	TX_SIN0U069,
	TX_SIN0U082,


	TX_SIN1_001,
	TX_SIN1_002,
	TX_SIN1_003,
	TX_SIN1_004,
	TX_SIN1_005,
	TX_SIN1_006,
	TX_SIN1_007,
	TX_SIN1_008,
	TX_SIN1_009,
	TX_SIN1_010,
	TX_SIN1_011,
	TX_SIN1_012,
	TX_SIN1_013,
	TX_SIN1_014,
	TX_SIN1_015,
	TX_SIN1_016,
	TX_SIN1_017,
	TX_SIN1_018,
	TX_SIN1_019,
	TX_SIN1_020,
	TX_SIN1_021,
	TX_SIN1_022,
	TX_SIN1_023,
	TX_SIN1_024,
	TX_SIN1_025,
	TX_SIN1_026,
	TX_SIN1_027,
	TX_SIN1_028,
	TX_SIN1_029,
	TX_SIN1_030,
	// UNUSED: 031
	TX_SIN1_S10,
	TX_SIN1_S17,
	TX_SIN1_S18,
	TX_SIN1_S20,
	TX_SIN1_S51,
	TX_SIN1_S85,
	TX_SIN1N000,
	TX_SIN1N001,
	TX_SIN1N002,
	TX_SIN1N003,
	TX_SIN1N004,
	TX_SIN1N005,
	TX_SIN1N006,
	TX_SIN1N007,
	TX_SIN1N008,
	TX_SIN1N009,
	TX_SIN1N010,
	TX_SIN1N011,
	TX_SIN1U070,


	TX_SIN2_001,
	TX_SIN2_002,
	TX_SIN2_003,
	TX_SIN2_004,
	TX_SIN2_005,
	TX_SIN2_006,
	TX_SIN2_007,
	TX_SIN2_008,
	TX_SIN2_009,
	TX_SIN2_010,
	// MISSING
	TX_SIN2_012,
	TX_SIN2_013,
	TX_SIN2_014,
	TX_SIN2_015,
	TX_SIN2_016,
	TX_SIN2_017,
	// MISSING
	TX_SIN2_019,
	TX_SIN2_020,
	TX_SIN2_021,
	TX_SIN2_022,
	TX_SIN2_023,
	TX_SIN2_024,
	TX_SIN2_025,
	TX_SIN2_026,
	TX_SIN2_027,
	TX_SIN2_028,
	TX_SIN2_029,
	TX_SIN2_030,
	TX_SIN2_031,
	TX_SIN2_032,
	TX_SIN2_033,
	TX_SIN2_034,
	TX_SIN2_035,
	// UNUSED (036)
	TX_SIN2_037,
	TX_SIN2_038,
	TX_SIN2_039,
	TX_SIN2_040,
	TX_SIN2_041,
	TX_SIN2_042,
	TX_SIN2_043,
	TX_SIN2_044,
	TX_SIN2_045,
	TX_SIN2_046,
	TX_SIN2_047,
	TX_SIN2_048,
	TX_SIN2_049,
	TX_SIN2_050,
	// UNUSED (051 -> 054; uhura voice substitute)
	TX_SIN2_F12,
	TX_SIN2_F26,
	TX_SIN2_S05,
	TX_SIN2_S16,
	TX_SIN2N000,
	TX_SIN2N001,
	TX_SIN2N002,
	TX_SIN2N003,
	TX_SIN2N004,
	TX_SIN2N005,
	TX_SIN2N006,
	TX_SIN2N007,
	TX_SIN2N008,
	TX_SIN2U085,
	TX_SIN2U096,
	TX_SIN2U097,
	// UNUSED: sin2_b35.voc (same as 036)


	TX_SIN3_001,
	TX_SIN3_002,
	TX_SIN3_003,
	TX_SIN3_004,
	TX_SIN3_005,
	TX_SIN3_006,
	TX_SIN3_007,
	TX_SIN3_008,
	TX_SIN3_009,
	TX_SIN3_010,
	TX_SIN3_011,
	TX_SIN3_012,
	TX_SIN3_013,
	TX_SIN3_014,
	TX_SIN3_015,
	TX_SIN3_016,
	TX_SIN3_017,
	TX_SIN3_018,
	TX_SIN3_019,
	TX_SIN3_020,
	TX_SIN3_021,
	TX_SIN3_022,
	TX_SIN3_023,
	TX_SIN3_024,
	TX_SIN3_025,
	TX_SIN3_026,
	TX_SIN3_027,
	// UNUSED (028; uhura voice substitute)
	TX_SIN3N000,
	TX_SIN3N001,
	TX_SIN3N002,
	TX_SIN3N003,
	TX_SIN3N004,
	TX_SIN3N005,
	TX_SIN3N006,
	TX_SIN3N007,
	TX_SIN3N008,
	TX_SIN3N009,
	TX_SIN3N010,
	TX_SIN3N011,
	TX_SIN3N012,
	TX_SIN3N013,
	TX_SIN3N014,
	TX_SIN3U072,
	TX_SIN3_LASERSETTING001, // Custom named text
	TX_SIN3_LASERSETTING010,
	TX_SIN3_LASERSETTING100,
	TX_SIN3_LASERCANCEL,


	TX_SIN4_001,
	TX_SIN4_002,
	TX_SIN4_003,
	TX_SIN4_004,
	TX_SIN4_005,
	TX_SIN4_006,
	TX_SIN4_007,
	TX_SIN4_008,
	TX_SIN4_009,
	TX_SIN4_010,
	TX_SIN4_011,
	TX_SIN4_012,
	TX_SIN4_013,
	TX_SIN4_014,
	TX_SIN4_015,
	TX_SIN4_016,
	TX_SIN4_017,
	TX_SIN4_018,
	TX_SIN4_019,
	TX_SIN4_020,
	TX_SIN4_021,
	TX_SIN4_022,
	TX_SIN4_023,
	TX_SIN4_024,
	TX_SIN4_025,
	TX_SIN4_026,
	TX_SIN4_027,
	TX_SIN4_028,
	TX_SIN4_029,
	TX_SIN4_030,
	TX_SIN4_031,
	TX_SIN4_032,
	// UNUSED (033 -> 039; uhura voice substitute)
	TX_SIN4N000,
	TX_SIN4N001,
	TX_SIN4N002,
	TX_SIN4N003,
	TX_SIN4N004,
	TX_SIN4N005,
	TX_SIN4N006,
	TX_SIN4N007,
	TX_SIN4N008,
	TX_SIN4N009,
	TX_SIN4N010,
	TX_SIN4N011,
	TX_SIN4N012,
	TX_SIN4N013,
	TX_SIN4U073,
	TX_SIN4U088,
	TX_SIN4U100,
	TX_SIN4U103,
	TX_SIN4U105,
	TX_SIN4U107,
	// UNUSED (sin4u83a; alternate version of sin4u83b)
	TX_SIN4U83B,


	TX_SIN5_001,
	TX_SIN5_002,
	TX_SIN5_003,
	TX_SIN5_004,
	TX_SIN5_005,
	TX_SIN5_006,
	TX_SIN5_007,
	TX_SIN5_008,
	TX_SIN5_009,
	TX_SIN5_010,
	TX_SIN5_011,
	TX_SIN5_012,
	TX_SIN5_013,
	TX_SIN5_014,
	TX_SIN5_015,
	TX_SIN5_016,
	TX_SIN5_017,
	TX_SIN5_018,
	TX_SIN5_019,
	TX_SIN5_020,
	TX_SIN5_021,
	TX_SIN5_022,
	TX_SIN5_023,
	TX_SIN5_024,
	TX_SIN5_025,
	TX_SIN5_026,
	TX_SIN5_027,
	TX_SIN5_028,
	TX_SIN5_029,
	TX_SIN5_030,
	TX_SIN5_031,
	TX_SIN5_032,
	TX_SIN5_033,
	TX_SIN5_034,
	TX_SIN5_035,
	TX_SIN5_036,
	TX_SIN5_037,
	TX_SIN5_038,
	TX_SIN5_039,
	TX_SIN5_040,
	TX_SIN5_041,
	TX_SIN5_042,
	TX_SIN5_043,
	TX_SIN5_044,
	TX_SIN5_045,
	TX_SIN5_046,
	TX_SIN5_S19,
	TX_SIN5N000,
	TX_SIN5N001,
	TX_SIN5N002,
	TX_SIN5N003,
	TX_SIN5N004,
	TX_SIN5N005,
	TX_SIN5N006,
	TX_SIN5N007,
	TX_SIN5N008,
	TX_SIN5N009,
	TX_SIN5N010,
	TX_SIN5N011,
	TX_SIN5N012,
	TX_SIN5N013,


	TX_VEN0_001,
	TX_VEN0_002,
	TX_VEN0_003,
	TX_VEN0_004,
	TX_VEN0_005,
	TX_VEN0_006,
	TX_VEN0_007,
	TX_VEN0_008,
	TX_VEN0_009,
	TX_VEN0_010,
	TX_VEN0_011,
	TX_VEN0_012,
	TX_VEN0_013,
	TX_VEN0_014,
	TX_VEN0_015,
	TX_VEN0_016,
	TX_VEN0_017,
	TX_VEN0_018,
	TX_VEN0_019,
	TX_VEN0_020,
	TX_VEN0_021,
	TX_VEN0_022,
	TX_VEN0_023,
	TX_VEN0_024,
	TX_VEN0_025,
	TX_VEN0_026,
	TX_VEN0_027,
	TX_VEN0_028,
	TX_VEN0_029,
	TX_VEN0_030,
	TX_VEN0_031,
	TX_VEN0_32,
	TX_VEN0_033,
	TX_VEN0_034,
	TX_VEN0_035,
	TX_VEN0_036,
	TX_VEN0_037,
	TX_VEN0_038,
	TX_VEN0_039,
	TX_VEN0_S12,
	// UNUSED: S13 -> S14 (same line S12, multiple recordings)
	TX_VEN0_S15,
	TX_VEN0_S52,
	TX_VEN0_S54,
	TX_VEN0N000,
	TX_VEN0N001,
	TX_VEN0N002,
	TX_VEN0N003,
	TX_VEN0N004,
	TX_VEN0N005,
	TX_VEN0N006,
	TX_VEN0N007,
	TX_VEN0N008,
	TX_VEN0N009,
	TX_VEN0N010,
	TX_VEN0N011,
	TX_VEN0N012,
	TX_VEN0N013,
	// MISSING
	TX_VEN0N015,
	TX_VEN0N016,
	TX_VEN0N017,
	TX_VEN0N018,
	TX_VEN0N019,
	// UNUSED: VEN0_F15


	TX_VEN1_001,
	TX_VEN1_002,
	// UNUSED
	TX_VEN1_004,
	TX_VEN1_005,
	TX_VEN1_006,
	TX_VEN1_007,
	TX_VEN1_008,
	TX_VEN1_009,
	TX_VEN1_010,
	TX_VEN1_011,
	TX_VEN1_012,
	TX_VEN1_013,
	TX_VEN1_014,
	TX_VEN1_015,
	TX_VEN1_016,
	TX_VEN1_F33,
	TX_VEN1N000,
	TX_VEN1N001,
	TX_VEN1N002,
	TX_VEN1N003,
	TX_VEN1N004,
	TX_VEN1N005,
	TX_VEN1N006,
	TX_VEN1N007,
	TX_VEN1N008,
	TX_VEN1N009,
	TX_VEN1N010,
	TX_VEN1N011,
	TX_VEN1N012,
	TX_VEN1N013,
	TX_VEN1N014,
	TX_VEN1N015,
	TX_VEN1N016,
	TX_VEN1N017,
	TX_VEN1N018,
	TX_VEN1N019,
	TX_VEN1N020,
	TX_VEN1N021,
	TX_VEN1N022,
	TX_VEN1N023,
	// UNUSED: VEN1NA18 (variant of VEN1N018)


	TX_VEN2_001,
	TX_VEN2_002,
	TX_VEN2_003,
	TX_VEN2_004,
	TX_VEN2_005,
	TX_VEN2_006,
	TX_VEN2_007,
	TX_VEN2_008,
	TX_VEN2_009,
	TX_VEN2_010,
	TX_VEN2_011,
	TX_VEN2_012,
	TX_VEN2_013,
	TX_VEN2_014,
	TX_VEN2_015,
	TX_VEN2_016,
	TX_VEN2_017,
	TX_VEN2_018,
	TX_VEN2_019,
	TX_VEN2_020,
	TX_VEN2_021,
	TX_VEN2_022,
	TX_VEN2_023, // UNUSED
	TX_VEN2_024,
	TX_VEN2_025,
	TX_VEN2_026,
	TX_VEN2_027,
	TX_VEN2_028,
	TX_VEN2_029,
	TX_VEN2_030,
	TX_VEN2_031,
	TX_VEN2_032,
	TX_VEN2_033,
	TX_VEN2_034,
	TX_VEN2_035,
	TX_VEN2_036,
	TX_VEN2_037,
	TX_VEN2_038,
	TX_VEN2_039,
	TX_VEN2_040,
	TX_VEN2_041,
	TX_VEN2_042,
	TX_VEN2_043,
	TX_VEN2_044,
	TX_VEN2_045,
	TX_VEN2_046,
	TX_VEN2_047,
	TX_VEN2_048, // UNUSED
	// UNUSED
	TX_VEN2_050, // UNUSED
	TX_VEN2_051,
	TX_VEN2_052,
	TX_VEN2_053, // UNUSED
	TX_VEN2_054,
	TX_VEN2_055,
	TX_VEN2_056,
	TX_VEN2_057,
	TX_VEN2_058,
	TX_VEN2_059,
	TX_VEN2_060,
	TX_VEN2_061,
	TX_VEN2_062,
	TX_VEN2_063,
	TX_VEN2_064,
	TX_VEN2_065,
	TX_VEN2_066,
	TX_VEN2_067,
	TX_VEN2_068,
	TX_VEN2_069,
	TX_VEN2_070,
	TX_VEN2_071,
	TX_VEN2_072,
	TX_VEN2_073,
	TX_VEN2_074,
	TX_VEN2_075,
	TX_VEN2_076, // UNUSED
	TX_VEN2_077,
	TX_VEN2_078,
	TX_VEN2_079,
	TX_VEN2_080,
	TX_VEN2_081,
	TX_VEN2_082,
	TX_VEN2_083,
	TX_VEN2_084,
	TX_VEN2_085,
	TX_VEN2_086,
	TX_VEN2_087,
	TX_VEN2_088,
	TX_VEN2_089,
	TX_VEN2_090,
	TX_VEN2_091,
	TX_VEN2_092,
	TX_VEN2_093,
	TX_VEN2_094,
	// UNUSED
	TX_VEN2_096,
	TX_VEN2_097,
	TX_VEN2_098,
	TX_VEN2_099,
	TX_VEN2_100,
	TX_VEN2_101,
	TX_VEN2_102,
	TX_VEN2_103,
	TX_VEN2_104,
	TX_VEN2_105,
	TX_VEN2_106,
	TX_VEN2_107, // UNUSED
	TX_VEN2_108,
	TX_VEN2_109,
	TX_VEN2_110, // UNUSED
	TX_VEN2_111,
	TX_VEN2_112,
	TX_VEN2_113,
	TX_VEN2_114,
	TX_VEN2_115,
	// UNUSED (116 -> 117; uhura voice substitute)
	TX_VEN2_ELA, // UNUSED
	TX_VEN2_ENT, // UNUSED
	TX_VEN2_F28,
	TX_VEN2_F29,
	TX_VEN2_F35,
	// UNUSED: VEN2L062, VEN2L063 (someone's voice substitute?)
	TX_VEN2_S09,
	TX_VEN2_SHI,
	TX_VEN2_TRA,
	TX_VEN2_WEA,
	TX_VEN2N000,
	TX_VEN2N001,
	TX_VEN2N002,
	TX_VEN2N003,
	TX_VEN2N004,
	TX_VEN2N005,
	TX_VEN2N006,
	TX_VEN2N007,
	TX_VEN2N008,
	TX_VEN2N009,
	TX_VEN2N010,
	TX_VEN2N011, // UNUSED
	TX_VEN2N012,
	TX_VEN2N013,
	// MISSING
	TX_VEN2N015,
	TX_VEN2N016,
	TX_VEN2N017,
	TX_VEN2N018, // UNUSED
	TX_VEN2N019,
	TX_VEN2N020,
	TX_VEN2N021,
	TX_VEN2N022,
	TX_VEN2N023,
	TX_VEN2N024,
	TX_VEN2N025,
	// UNUSED
	TX_VEN2N027,
	TX_VEN2N028,
	TX_VEN2N029,
	TX_VEN2N030,
	TX_VEN2N031,
	TX_VEN2N032,
	TX_VEN2N033,
	TX_VEN2N034,
	TX_VEN2N035,
	// UNUSED: 036, 037
	TX_VEN2N038, // UNUSED
	TX_VEN2N039,
	// UNUSED: N040 -> N043 (options for a menu?)
	// UNUSED: VEN2NA25 (Alternate for VEN2N025)
	// UNUSED: VEN2S072 (similar to VEN2_027)
	TX_VEN2U093,
	TX_VEN2U094,
	TX_VEN2_HAIL_ELASI, // Custom named text
	TX_VEN2_HAIL_ENT,
	TX_VEN2_CANCEL,


	TX_VEN3_001,
	TX_VEN3_002,
	TX_VEN3_003,
	TX_VEN3_004,
	TX_VEN3_005,
	TX_VEN3_006,
	TX_VEN3_007,
	TX_VEN3_008,
	TX_VEN3_009,
	TX_VEN3_010,
	TX_VEN3_011,
	TX_VEN3_012,
	TX_VEN3_013,
	TX_VEN3_014,
	TX_VEN3_015,
	TX_VEN3_016,
	TX_VEN3_017,
	TX_VEN3_018,
	TX_VEN3N000,
	TX_VEN3N001,
	TX_VEN3N002,
	TX_VEN3N003,
	TX_VEN3N004,
	TX_VEN3N005,
	TX_VEN3N006,
	TX_VEN3N007,
	// UNUSED
	TX_VEN3N009,
	TX_VEN3N010,
	TX_VEN3N011,
	TX_VEN3N012,
	TX_VEN3N013,
	TX_VEN3N014,


	TX_VEN4_001,
	TX_VEN4_002,
	TX_VEN4_003,
	TX_VEN4_004,
	TX_VEN4_005,
	TX_VEN4_006,
	TX_VEN4_007,
	TX_VEN4_008,
	TX_VEN4_009,
	TX_VEN4_010,
	TX_VEN4_011,
	TX_VEN4_012,
	TX_VEN4_013,
	TX_VEN4_014,
	TX_VEN4_015,
	TX_VEN4_016,
	TX_VEN4_017,
	TX_VEN4_018, // UNUSED
	TX_VEN4_019,
	TX_VEN4_020,
	TX_VEN4_021,
	TX_VEN4_022,
	TX_VEN4N000,
	TX_VEN4N001,
	TX_VEN4N002,
	TX_VEN4N003,
	TX_VEN4N004,
	TX_VEN4N005,
	TX_VEN4N006,
	TX_VEN4N007,
	TX_VEN4N008,
	TX_VEN4N009,
	TX_VEN4N010,
	TX_VEN4N011,
	TX_VEN4N012,
	TX_VEN4N013,
	TX_VEN4N014,
	TX_VEN4N015,
	TX_VEN4N016,
	TX_VEN4N017,


	TX_VEN5_001,
	TX_VEN5_002,
	TX_VEN5_003,
	TX_VEN5_004,
	TX_VEN5_005,
	TX_VEN5_006,
	TX_VEN5_007,
	TX_VEN5_008,
	TX_VEN5_009,
	TX_VEN5_010,
	TX_VEN5_011,
	TX_VEN5_012,
	TX_VEN5_013,
	// MISSING
	TX_VEN5_015,
	TX_VEN5_016,
	TX_VEN5_017,
	TX_VEN5_018,
	TX_VEN5_019,
	// UNUSED: 020 (identical to R20)
	TX_VEN5_R19,
	TX_VEN5_R20,
	TX_VEN5N000,
	TX_VEN5N001,
	TX_VEN5N002,
	TX_VEN5N003,
	TX_VEN5N004,
	TX_VEN5N005,
	TX_VEN5N006,
	TX_VEN5N007,
	TX_VEN5N008,
	TX_VEN5N009,
	TX_VEN5N010,


	TX_VEN6_001,
	TX_VEN6_002,
	TX_VEN6_003,
	// UNUSED
	TX_VEN6_005,
	TX_VEN6_006,
	TX_VEN6_007,
	TX_VEN6_008,
	TX_VEN6_009,
	TX_VEN6_010,
	TX_VEN6_011,
	TX_VEN6_012,
	TX_VEN6_013,
	TX_VEN6_014,
	TX_VEN6_015,
	TX_VEN6_016,
	TX_VEN6_017,
	TX_VEN6_018,
	TX_VEN6_019,
	TX_VEN6_020,
	TX_VEN6_021,
	TX_VEN6_022,
	TX_VEN6_023,
	TX_VEN6N000,
	TX_VEN6N001,
	TX_VEN6N002,
	TX_VEN6N003,
	// UNUSED
	TX_VEN6N005,
	TX_VEN6N006,
	TX_VEN6N007,
	TX_VEN6N008,
	TX_VEN6N009,
	TX_VEN6N010,
	TX_VEN6N011,
	TX_VEN6N012,
	TX_VEN6N013,
	// MISSING
	TX_VEN6N015,
	TX_VEN6N016,
	TX_VEN6N017,
	TX_VEN6N018,
	TX_VEN6N019,
	TX_VEN6N020,
	// UNUSED
	TX_VEN6N022,
	// UNUSED
	TX_VEN6N024,
	TX_VEN6N025,


	TX_VEN7_001,
	// UNUSED
	TX_VEN7_003,
	// UNUSED
	TX_VEN7_005,
	TX_VEN7_006,
	TX_VEN7_007,
	TX_VEN7N000,
	TX_VEN7N001,
	TX_VEN7N002,
	TX_VEN7N003,
	TX_VEN7N004,
	TX_VEN7N005,
	TX_VEN7N006,
	TX_VEN7N007,
	TX_VEN7N008,
	TX_VEN7N009,


	TX_VEN8_001,
	TX_VEN8_002,
	TX_VEN8_003,
	TX_VEN8_004,
	TX_VEN8_005,
	TX_VEN8_006,
	TX_VEN8_007,
	TX_VEN8_008,
	TX_VEN8_009,
	TX_VEN8_010,
	TX_VEN8_011,
	TX_VEN8_012,
	TX_VEN8_013,
	TX_VEN8_014,
	TX_VEN8_015,
	TX_VEN8_016, // UNUSED
	// UNUSED
	TX_VEN8_018,
	// UNUSED
	TX_VEN8_020,
	TX_VEN8_021,
	// UNUSED
	TX_VEN8_023,
	TX_VEN8_024, // UNUSED
	TX_VEN8_025,
	TX_VEN8_026,
	TX_VEN8_027,
	TX_VEN8_028,
	TX_VEN8_029,
	TX_VEN8_030,
	TX_VEN8_031,
	TX_VEN8_032,
	TX_VEN8_033,
	TX_VEN8_034,
	TX_VEN8_035,
	TX_VEN8_036,
	TX_VEN8_037,
	TX_VEN8_038,
	TX_VEN8_039,
	TX_VEN8_040,
	TX_VEN8_041,
	TX_VEN8_042,
	TX_VEN8N000,
	TX_VEN8N001,
	// UNUSED
	TX_VEN8N003,
	TX_VEN8N004,
	TX_VEN8N005,
	TX_VEN8N006,
	TX_VEN8N007,
	TX_VEN8N008,
	TX_VEN8N009,
	TX_VEN8N010,
	// UNUSED (N011)


	TX_VENA_F32,
	TX_VENA_F34,
	TX_VENA_F40,
	TX_VENA_F41,


	TX_SPOKCOFF,
	TX_STATICU1,


	TX_END
};

// defined in text.cpp
extern const char *const g_gameStrings[];

} // End of namespace StarTrek

#endif
