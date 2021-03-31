/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2019
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CDriveNextModerator.cpp
* @ingroup      HMIComponent
* @author       Nandkishor Lokhande.
* @brief        CDriveNextModerator Static Class to contain all validation and conversion methods for DriveNext.
*/

#include "CDriveNextModerator.h"
#include "logging.h"

CallStatus CDriveNextModerator::sm_eProxyEnumValidationStatus = CallStatus::UNKNOWN;

CDriveNextModerator::CDriveNextModerator()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    //Do Nothing!
}

bool CDriveNextModerator::validateDNProxyEnumValue()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    if (CallStatus::UNKNOWN == sm_eProxyEnumValidationStatus)
    {
        sm_eProxyEnumValidationStatus = CallStatus::SUCCESS;
        for (int iProxyEnumValue = driveProTypeCollection::eSignalNames::Literal::UNKONWN; iProxyEnumValue <= driveProTypeCollection::eSignalNames::Literal::TOTAL_COUNT; iProxyEnumValue++)
        {
            int iHmiEnumValue = static_cast<int>(convertToDNHmiSignalEnumValue(static_cast<driveProTypeCollection::eSignalNames::Literal>(iProxyEnumValue)));
            int iProxyEnumValueOutCome = static_cast<int>(convertToDNProxySignalEnumValue(static_cast<EDriveNextSignalTypes>(iHmiEnumValue)));
            if (iProxyEnumValueOutCome != iProxyEnumValue)
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, Unhandled DNProxySignalEnumValue-> iProxyEnumValue:%d, iHmiEnumValue:%d, iProxyEnumValueOutCome:%d", __FUNCTION__, iProxyEnumValue, iHmiEnumValue, iProxyEnumValueOutCome);
                sm_eProxyEnumValidationStatus = CallStatus::INVALID_VALUE;
            }
        }
        LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, Validated and result is :%d", __FUNCTION__, static_cast<int>(sm_eProxyEnumValidationStatus));
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, Already validated and result is :%d", __FUNCTION__, static_cast<int>(sm_eProxyEnumValidationStatus));
    }
    return (CallStatus::SUCCESS == sm_eProxyEnumValidationStatus);
}

driveProTypeCollection::eSignalNames::Literal CDriveNextModerator::convertToDNProxySignalEnumValue(EDriveNextSignalTypes eHmiValue)
{
    driveProTypeCollection::eSignalNames::Literal eProxyValue = driveProTypeCollection::eSignalNames::Literal::UNKONWN;
    switch(eHmiValue)
    {
    case EDriveNextSignalTypes::DRIVENEXT_SIG_UNKNOWN:                                                      {/*eProxyValue=driveProTypeCollection::eSignalNames::Literal::UNKONWN;*/}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_FUELECOINSTRATING:                                {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_FUELECOINSTRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_FUELECOCUMRATING:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_FUELECOCUMRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIME_ENGINEIDLE:                             {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALTIME_ENGINEIDLE;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_IDLETIME:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_IDLETIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_IDLETIMEPER:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_IDLETIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALFUELIDLE:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALFUELIDLE;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIME_RPMEFFINFO:                             {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALTIME_RPMEFFINFO;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALDIST:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALDIST;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMTIMEAMBER:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_EFF_RPMTIMEAMBER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMTIMEAMBERPER:                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_EFF_RPMTIMEAMBERPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMTIMEGREEN:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_EFF_RPMTIMEGREEN;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMTIMEGREENPER:                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_EFF_RPMTIMEGREENPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMTIMERED:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_EFF_RPMTIMERED;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMTIMEREDPER:                                {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_EFF_RPMTIMEREDPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMDISTAMBER:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_EFF_RPMDISTAMBER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMDISTAMBERPER:                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_EFF_RPMDISTAMBERPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMDISTGREEN:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_EFF_RPMDISTGREEN;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMDISTGREENPER:                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_EFF_RPMDISTGREENPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMDISTRED:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_EFF_RPMDISTRED;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMDISTREDPER:                                {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_EFF_RPMDISTREDPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGENG_RPM:                                       {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_AVGENG_RPM;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIME_ACON:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALTIME_ACON;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AC_ONTIME:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_AC_ONTIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AC_ONTIMEPER:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_AC_ONTIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIME_CLT_ACC:                                {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALTIME_CLT_ACC;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_CLT_ACCTIME:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_CLT_ACCTIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_CLT_ACCTIMEPER:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_CLT_ACCTIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_BRKINSTRATING:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_BRKINSTRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCLN:                                            {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_ACCLN;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_NOOFBRKCYCLE:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_NOOFBRKCYCLE;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_BRKCUMRATING:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_BRKCUMRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALBRK:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALBRK;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_NORMALBRK:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_NORMALBRK;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_NORMALBRKPER:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_NORMALBRKPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_MODERATEBRK:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_MODERATEBRK;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_MODERATEBRKPER:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_MODERATEBRKPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_HEAVYBRK:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_HEAVYBRK;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_HEAVYBRKPER:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_HEAVYBRKPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_PANICBRK:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_PANICBRK;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_PANICBRKPER:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_PANICBRKPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_HARSHBRK:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_HARSHBRK;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_HARSHBRKPER:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_HARSHBRKPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGBRKCOUNT:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_AVGBRKCOUNT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ODODISTPERTRIP_BRAKING:                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_ODODISTPERTRIP_BRAKING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCINSTRATING:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_ACCINSTRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCCUMRATING:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_ACCCUMRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTRAVELTIME:                                  {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALTRAVELTIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALACCPEDALPRESSTIME:                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALACCPEDALPRESSTIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCPEDALPRESSRANGE1:                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_ACCPEDALPRESSRANGE1;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCPEDALPRESSRANGE1PER:                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_ACCPEDALPRESSRANGE1PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCPEDALPRESSRANGE2:                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_ACCPEDALPRESSRANGE2;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCPEDALPRESSRANGE2PER:                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_ACCPEDALPRESSRANGE2PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCPEDALPRESSRANGE3:                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_ACCPEDALPRESSRANGE3;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCPEDALPRESSRANGE3PER:                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_ACCPEDALPRESSRANGE3PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCPEDALPRESSRANGE4:                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_ACCPEDALPRESSRANGE4;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCPEDALPRESSRANGE4PER:                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_ACCPEDALPRESSRANGE4PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCPEDALPRESSNO:                                  {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_ACCPEDALPRESSNO;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCPEDALPRESNOPER:                                {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_ACCPEDALPRESNOPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGACCPEDALPOS:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_AVGACCPEDALPOS;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCHARSHCOUNT:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_ACCHARSHCOUNT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_VEHICLE_TXMNVARIANT:                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_VEHICLE_TXMNVARIANT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_GSINSTRATING:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_GSINSTRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_GSCUMRATING:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_GSCUMRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALDISTVALIDGEAR_GEARSHIFT:                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALDISTVALIDGEAR_GEARSHIFT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIMEVALIDGEAR_GEARSHIFT:                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALTIMEVALIDGEAR_GEARSHIFT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR1:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TIMEGEAR1;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR1:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_DISTGEAR1;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR1PER:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TIMEGEAR1PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR1PER:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_DISTGEAR1PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR2:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TIMEGEAR2;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR2:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_DISTGEAR2;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR2PER:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TIMEGEAR2PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR2PER:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_DISTGEAR2PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR3:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TIMEGEAR3;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR3:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_DISTGEAR3;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR3PER:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TIMEGEAR3PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR3PER:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_DISTGEAR3PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR4:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TIMEGEAR4;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR4:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_DISTGEAR4;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR4PER:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TIMEGEAR4PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR4PER:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_DISTGEAR4PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR5:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TIMEGEAR5;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR5:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_DISTGEAR5;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR5PER:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TIMEGEAR5PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR5PER:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_DISTGEAR5PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR6:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TIMEGEAR6;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR6:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_DISTGEAR6;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR6PER:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TIMEGEAR6PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR6PER:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_DISTGEAR6PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_MOSTTIMEGEAR:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_MOSTTIMEGEAR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALDISTVALIDGEAR:                               {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALDISTVALIDGEAR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALDISTWRONGGEAR:                               {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALDISTWRONGGEAR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALDISTDOWNINDI:                                {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALDISTDOWNINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALDISTUPINDI:                                  {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALDISTUPINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGDISTWRONGINDI:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_AVGDISTWRONGINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGDISTDOWNINDI:                                  {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_AVGDISTDOWNINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGDISTUPINDI:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_AVGDISTUPINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALDISTWRONGGEARPER:                            {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALDISTWRONGGEARPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALDISTDOWNINDIPER:                             {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALDISTDOWNINDIPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALDISTUPINDIPER:                               {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALDISTUPINDIPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIMEVALIDGEAR:                               {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALTIMEVALIDGEAR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIMEWRONGGEAR:                               {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALTIMEWRONGGEAR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIMEDOWNINDI:                                {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALTIMEDOWNINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIMEUPINDI:                                  {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALTIMEUPINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIMEWRONGGEARPER:                            {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALTIMEWRONGGEARPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIMEDOWNINDIPER:                             {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALTIMEDOWNINDIPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIMEUPINDIPER:                               {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALTIMEUPINDIPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALCOUNTWRONGGEAR:                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALCOUNTWRONGGEAR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALCOUNTDOWNINDI:                               {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALCOUNTDOWNINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALCOUNTUPINDI:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALCOUNTUPINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALCOUNTDOWNINDIPER:                            {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALCOUNTDOWNINDIPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALCOUNTUPINDIPER:                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALCOUNTUPINDIPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGCOUNTUPINDI:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_AVGCOUNTUPINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGCOUNTDOWNINDI:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_AVGCOUNTDOWNINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIMECORRECTGEARPER:                          {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALTIMECORRECTGEARPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGGEARSHIFT:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_AVGGEARSHIFT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_NOOFGEARSHIFT:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_NOOFGEARSHIFT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ODODISTPERTRIP:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_ODODISTPERTRIP;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOPSPEED:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOPSPEED;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DRIVEINSTRATING:                                  {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_DRIVEINSTRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DRIVECUMURATING:                                  {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_DRIVECUMURATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SPEEDBAND1TIME:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_SPEEDBAND1TIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SPEEDBAND1TIMEPER:                                {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_SPEEDBAND1TIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SPEEDBAND2TIME:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_SPEEDBAND2TIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SPEEDBAND2TIMEPER:                                {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_SPEEDBAND2TIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SPEEDBAND3TIME:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_SPEEDBAND3TIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SPEEDBAND3TIMEPER:                                {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_SPEEDBAND3TIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SPEEDBAND4TIME:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_SPEEDBAND4TIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SPEEDBAND4TIMEPER:                                {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_SPEEDBAND4TIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TRIPDIST:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TRIPDIST;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TRIPDURATION:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TRIPDURATION;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGSPEED:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_AVGSPEED;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGFUELECO:                                       {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_AVGFUELECO;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_OVERALLINSTRATING:                                {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_OVERALLINSTRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_OVERALLCUMURATING:                                {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_OVERALLCUMURATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_PERTIMEWITHOUTSEATBELT:                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_PERTIMEWITHOUTSEATBELT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_PERTIMEWITHSEATBELT:                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_PERTIMEWITHSEATBELT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SEATBELTFACTOR:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_SEATBELTFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_NOOFTIMEWITHOUTSEATBELT:                          {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_NOOFTIMEWITHOUTSEATBELT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_NOOFTIMEWITHSEATBELT:                             {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_NOOFTIMEWITHSEATBELT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_NOOFTIMEWITHOUTSEATBELTPER:                       {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_NOOFTIMEWITHOUTSEATBELTPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DOORCLOSETIMEPER:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_DOORCLOSETIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DOOROPENTIMEPER:                                  {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_DOOROPENTIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEHIGHSPEEDCLTBRKPRESSEDPER:                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TIMEHIGHSPEEDCLTBRKPRESSEDPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIMEHIGHSPEEDPER:                            {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALTIMEHIGHSPEEDPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SRSFACTOR:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_SRSFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TEABREAKFACTOR:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TEABREAKFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TRLFACTOR:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TRLFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TLLFACTOR:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TLLFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TBLFACTOR:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TBLFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TFLFACTOR:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TFLFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TPLFACTOR:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TPLFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TRVLFACTOR:                                       {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TRVLFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_BRKFLDFACTOR:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_BRKFLDFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_OILPRFACTOR:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_OILPRFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_WIFFACTOR:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_WIFFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_VEHICLEHEALTH:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_VEHICLEHEALTH;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SAFETYINSTRATING:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_SAFETYINSTRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SAFETYCUMRATING:                                  {eProxyValue=driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_SAFETYCUMRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_FUELECOINSTRATING:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_FUELECOINSTRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_FUELECOCUMRATING:                                       {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_FUELECOCUMRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALTIME_ENGINEIDLE:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALTIME_ENGINEIDLE;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_IDLETIME:                                               {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_IDLETIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_IDLETIMEPER:                                            {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_IDLETIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALFUELIDLE:                                          {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALFUELIDLE;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALTIME_RPMEFFINFO:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALTIME_RPMEFFINFO;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALDIST:                                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALDIST;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_EFF_RPMTIMEAMBER:                                       {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_EFF_RPMTIMEAMBER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_EFF_RPMTIMEAMBERPER:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_EFF_RPMTIMEAMBERPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_EFF_RPMTIMEGREEN:                                       {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_EFF_RPMTIMEGREEN;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_EFF_RPMTIMEGREENPER:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_EFF_RPMTIMEGREENPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_EFF_RPMTIMERED:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_EFF_RPMTIMERED;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_EFF_RPMTIMEREDPER:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_EFF_RPMTIMEREDPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_EFF_RPMDISTAMBER:                                       {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_EFF_RPMDISTAMBER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_EFF_RPMDISTAMBERPER:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_EFF_RPMDISTAMBERPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_EFF_RPMDISTGREEN:                                       {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_EFF_RPMDISTGREEN;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_EFF_RPMDISTGREENPER:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_EFF_RPMDISTGREENPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_EFF_RPMDISTRED:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_EFF_RPMDISTRED;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_EFF_RPMDISTREDPER:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_EFF_RPMDISTREDPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_AVGENG_RPM:                                             {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_AVGENG_RPM;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALTIME_ACON:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALTIME_ACON;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_AC_ONTIME:                                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_AC_ONTIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_AC_ONTIMEPER:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_AC_ONTIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALTIME_CLT_ACC:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALTIME_CLT_ACC;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_CLT_ACCTIME:                                            {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_CLT_ACCTIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_CLT_ACCTIMEPER:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_CLT_ACCTIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_BRKINSTRATING:                                          {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_BRKINSTRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_ACCLN:                                                  {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_ACCLN;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_NOOFBRKCYCLE:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_NOOFBRKCYCLE;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_BRKCUMRATING:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_BRKCUMRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALBRK:                                               {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALBRK;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_NORMALBRK:                                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_NORMALBRK;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_NORMALBRKPER:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_NORMALBRKPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_MODERATEBRK:                                            {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_MODERATEBRK;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_MODERATEBRKPER:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_MODERATEBRKPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_HEAVYBRK:                                               {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_HEAVYBRK;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_HEAVYBRKPER:                                            {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_HEAVYBRKPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_PANICBRK:                                               {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_PANICBRK;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_PANICBRKPER:                                            {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_PANICBRKPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_HARSHBRK:                                               {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_HARSHBRK;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_HARSHBRKPER:                                            {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_HARSHBRKPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_AVGBRKCOUNT:                                            {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_AVGBRKCOUNT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_ODODISTPERTRIP_BRAKING:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_ODODISTPERTRIP_BRAKING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_ACCINSTRATING:                                          {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_ACCINSTRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_ACCCUMRATING:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_ACCCUMRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALTRAVELTIME:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALTRAVELTIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALACCPEDALPRESSTIME:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALACCPEDALPRESSTIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_ACCPEDALPRESSRANGE1:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_ACCPEDALPRESSRANGE1;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_ACCPEDALPRESSRANGE1PER:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_ACCPEDALPRESSRANGE1PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_ACCPEDALPRESSRANGE2:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_ACCPEDALPRESSRANGE2;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_ACCPEDALPRESSRANGE2PER:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_ACCPEDALPRESSRANGE2PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_ACCPEDALPRESSRANGE3:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_ACCPEDALPRESSRANGE3;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_ACCPEDALPRESSRANGE3PER:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_ACCPEDALPRESSRANGE3PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_ACCPEDALPRESSRANGE4:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_ACCPEDALPRESSRANGE4;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_ACCPEDALPRESSRANGE4PER:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_ACCPEDALPRESSRANGE4PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_ACCPEDALPRESSNO:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_ACCPEDALPRESSNO;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_ACCPEDALPRESNOPER:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_ACCPEDALPRESNOPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_AVGACCPEDALPOS:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_AVGACCPEDALPOS;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_ACCHARSHCOUNT:                                          {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_ACCHARSHCOUNT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_VEHICLE_TXMNVARIANT:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_VEHICLE_TXMNVARIANT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_GSINSTRATING:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_GSINSTRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_GSCUMRATING:                                            {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_GSCUMRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALDISTVALIDGEAR_GEARSHIFT:                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALDISTVALIDGEAR_GEARSHIFT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALTIMEVALIDGEAR_GEARSHIFT:                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALTIMEVALIDGEAR_GEARSHIFT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TIMEGEAR1:                                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TIMEGEAR1;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_DISTGEAR1:                                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_DISTGEAR1;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TIMEGEAR1PER:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TIMEGEAR1PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_DISTGEAR1PER:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_DISTGEAR1PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TIMEGEAR2:                                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TIMEGEAR2;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_DISTGEAR2:                                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_DISTGEAR2;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TIMEGEAR2PER:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TIMEGEAR2PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_DISTGEAR2PER:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_DISTGEAR2PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TIMEGEAR3:                                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TIMEGEAR3;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_DISTGEAR3:                                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_DISTGEAR3;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TIMEGEAR3PER:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TIMEGEAR3PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_DISTGEAR3PER:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_DISTGEAR3PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TIMEGEAR4:                                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TIMEGEAR4;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_DISTGEAR4:                                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_DISTGEAR4;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TIMEGEAR4PER:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TIMEGEAR4PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_DISTGEAR4PER:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_DISTGEAR4PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TIMEGEAR5:                                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TIMEGEAR5;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_DISTGEAR5:                                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_DISTGEAR5;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TIMEGEAR5PER:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TIMEGEAR5PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_DISTGEAR5PER:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_DISTGEAR5PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TIMEGEAR6:                                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TIMEGEAR6;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_DISTGEAR6:                                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_DISTGEAR6;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TIMEGEAR6PER:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TIMEGEAR6PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_DISTGEAR6PER:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_DISTGEAR6PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_MOSTTIMEGEAR:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_MOSTTIMEGEAR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALDISTVALIDGEAR:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALDISTVALIDGEAR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALDISTWRONGGEAR:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALDISTWRONGGEAR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALDISTDOWNINDI:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALDISTDOWNINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALDISTUPINDI:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALDISTUPINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_AVGDISTWRONGINDI:                                       {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_AVGDISTWRONGINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_AVGDISTDOWNINDI:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_AVGDISTDOWNINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_AVGDISTUPINDI:                                          {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_AVGDISTUPINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALDISTWRONGGEARPER:                                  {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALDISTWRONGGEARPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALDISTDOWNINDIPER:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALDISTDOWNINDIPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALDISTUPINDIPER:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALDISTUPINDIPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALTIMEVALIDGEAR:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALTIMEVALIDGEAR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALTIMEWRONGGEAR:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALTIMEWRONGGEAR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALTIMEDOWNINDI:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALTIMEDOWNINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALTIMEUPINDI:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALTIMEUPINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALTIMEWRONGGEARPER:                                  {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALTIMEWRONGGEARPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALTIMEDOWNINDIPER:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALTIMEDOWNINDIPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALTIMEUPINDIPER:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALTIMEUPINDIPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALCOUNTWRONGGEAR:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALCOUNTWRONGGEAR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALCOUNTDOWNINDI:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALCOUNTDOWNINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALCOUNTUPINDI:                                       {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALCOUNTUPINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALCOUNTDOWNINDIPER:                                  {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALCOUNTDOWNINDIPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALCOUNTUPINDIPER:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALCOUNTUPINDIPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_AVGCOUNTUPINDI:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_AVGCOUNTUPINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_AVGCOUNTDOWNINDI:                                       {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_AVGCOUNTDOWNINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALTIMECORRECTGEARPER:                                {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALTIMECORRECTGEARPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_AVGGEARSHIFT:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_AVGGEARSHIFT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_NOOFGEARSHIFT:                                          {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_NOOFGEARSHIFT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_ODODISTPERTRIP:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_ODODISTPERTRIP;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOPSPEED:                                               {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TOPSPEED;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_DRIVEINSTRATING:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_DRIVEINSTRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_DRIVECUMURATING:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_DRIVECUMURATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_SPEEDBAND1TIME:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_SPEEDBAND1TIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_SPEEDBAND1TIMEPER:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_SPEEDBAND1TIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_SPEEDBAND2TIME:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_SPEEDBAND2TIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_SPEEDBAND2TIMEPER:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_SPEEDBAND2TIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_SPEEDBAND3TIME:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_SPEEDBAND3TIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_SPEEDBAND3TIMEPER:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_SPEEDBAND3TIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_SPEEDBAND4TIME:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_SPEEDBAND4TIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_SPEEDBAND4TIMEPER:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_SPEEDBAND4TIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TRIPDIST:                                               {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TRIPDIST;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TRIPDURATION:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TRIPDURATION;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_AVGSPEED:                                               {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_AVGSPEED;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_AVGFUELECO:                                             {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_AVGFUELECO;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_OVERALLINSTRATING:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_OVERALLINSTRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_OVERALLCUMURATING:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_OVERALLCUMURATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_PERTIMEWITHOUTSEATBELT:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_PERTIMEWITHOUTSEATBELT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_PERTIMEWITHSEATBELT:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_PERTIMEWITHSEATBELT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_SEATBELTFACTOR:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_SEATBELTFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_NOOFTIMEWITHOUTSEATBELT:                                {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_NOOFTIMEWITHOUTSEATBELT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_NOOFTIMEWITHSEATBELT:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_NOOFTIMEWITHSEATBELT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_NOOFTIMEWITHOUTSEATBELTPER:                             {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_NOOFTIMEWITHOUTSEATBELTPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_DOORCLOSETIMEPER:                                       {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_DOORCLOSETIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_DOOROPENTIMEPER:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_DOOROPENTIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TIMEHIGHSPEEDCLTBRKPRESSEDPER:                          {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TIMEHIGHSPEEDCLTBRKPRESSEDPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALTIMEHIGHSPEEDPER:                                  {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALTIMEHIGHSPEEDPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_SRSFACTOR:                                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_SRSFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TEABREAKFACTOR:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TEABREAKFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TRLFACTOR:                                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TRLFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TLLFACTOR:                                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TLLFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TBLFACTOR:                                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TBLFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TFLFACTOR:                                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TFLFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TPLFACTOR:                                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TPLFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TRVLFACTOR:                                             {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_TRVLFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_BRKFLDFACTOR:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_BRKFLDFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_OILPRFACTOR:                                            {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_OILPRFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_WIFFACTOR:                                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_WIFFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_VEHICLEHEALTH:                                          {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_VEHICLEHEALTH;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_SAFETYINSTRATING:                                       {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_SAFETYINSTRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_SAFETYCUMRATING:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPA_SAFETYCUMRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_FUELECOINSTRATING:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_FUELECOINSTRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_FUELECOCUMRATING:                                       {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_FUELECOCUMRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALTIME_ENGINEIDLE:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALTIME_ENGINEIDLE;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_IDLETIME:                                               {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_IDLETIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_IDLETIMEPER:                                            {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_IDLETIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALFUELIDLE:                                          {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALFUELIDLE;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALTIME_RPMEFFINFO:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALTIME_RPMEFFINFO;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALDIST:                                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALDIST;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_EFF_RPMTIMEAMBER:                                       {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_EFF_RPMTIMEAMBER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_EFF_RPMTIMEAMBERPER:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_EFF_RPMTIMEAMBERPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_EFF_RPMTIMEGREEN:                                       {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_EFF_RPMTIMEGREEN;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_EFF_RPMTIMEGREENPER:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_EFF_RPMTIMEGREENPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_EFF_RPMTIMERED:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_EFF_RPMTIMERED;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_EFF_RPMTIMEREDPER:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_EFF_RPMTIMEREDPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_EFF_RPMDISTAMBER:                                       {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_EFF_RPMDISTAMBER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_EFF_RPMDISTAMBERPER:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_EFF_RPMDISTAMBERPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_EFF_RPMDISTGREEN:                                       {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_EFF_RPMDISTGREEN;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_EFF_RPMDISTGREENPER:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_EFF_RPMDISTGREENPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_EFF_RPMDISTRED:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_EFF_RPMDISTRED;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_EFF_RPMDISTREDPER:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_EFF_RPMDISTREDPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_AVGENG_RPM:                                             {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_AVGENG_RPM;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALTIME_ACON:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALTIME_ACON;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_AC_ONTIME:                                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_AC_ONTIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_AC_ONTIMEPER:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_AC_ONTIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALTIME_CLT_ACC:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALTIME_CLT_ACC;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_CLT_ACCTIME:                                            {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_CLT_ACCTIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_CLT_ACCTIMEPER:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_CLT_ACCTIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_BRKINSTRATING:                                          {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_BRKINSTRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_ACCLN:                                                  {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_ACCLN;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_NOOFBRKCYCLE:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_NOOFBRKCYCLE;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_BRKCUMRATING:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_BRKCUMRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALBRK:                                               {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALBRK;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_NORMALBRK:                                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_NORMALBRK;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_NORMALBRKPER:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_NORMALBRKPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_MODERATEBRK:                                            {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_MODERATEBRK;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_MODERATEBRKPER:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_MODERATEBRKPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_HEAVYBRK:                                               {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_HEAVYBRK;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_HEAVYBRKPER:                                            {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_HEAVYBRKPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_PANICBRK:                                               {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_PANICBRK;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_PANICBRKPER:                                            {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_PANICBRKPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_HARSHBRK:                                               {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_HARSHBRK;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_HARSHBRKPER:                                            {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_HARSHBRKPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_AVGBRKCOUNT:                                            {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_AVGBRKCOUNT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_ODODISTPERTRIP_BRAKING:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_ODODISTPERTRIP_BRAKING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_ACCINSTRATING:                                          {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_ACCINSTRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_ACCCUMRATING:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_ACCCUMRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALTRAVELTIME:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALTRAVELTIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALACCPEDALPRESSTIME:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALACCPEDALPRESSTIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_ACCPEDALPRESSRANGE1:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_ACCPEDALPRESSRANGE1;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_ACCPEDALPRESSRANGE1PER:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_ACCPEDALPRESSRANGE1PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_ACCPEDALPRESSRANGE2:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_ACCPEDALPRESSRANGE2;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_ACCPEDALPRESSRANGE2PER:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_ACCPEDALPRESSRANGE2PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_ACCPEDALPRESSRANGE3:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_ACCPEDALPRESSRANGE3;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_ACCPEDALPRESSRANGE3PER:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_ACCPEDALPRESSRANGE3PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_ACCPEDALPRESSRANGE4:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_ACCPEDALPRESSRANGE4;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_ACCPEDALPRESSRANGE4PER:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_ACCPEDALPRESSRANGE4PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_ACCPEDALPRESSNO:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_ACCPEDALPRESSNO;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_ACCPEDALPRESNOPER:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_ACCPEDALPRESNOPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_AVGACCPEDALPOS:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_AVGACCPEDALPOS;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_ACCHARSHCOUNT:                                          {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_ACCHARSHCOUNT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_VEHICLE_TXMNVARIANT:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_VEHICLE_TXMNVARIANT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_GSINSTRATING:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_GSINSTRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_GSCUMRATING:                                            {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_GSCUMRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALDISTVALIDGEAR_GEARSHIFT:                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALDISTVALIDGEAR_GEARSHIFT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALTIMEVALIDGEAR_GEARSHIFT:                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALTIMEVALIDGEAR_GEARSHIFT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TIMEGEAR1:                                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TIMEGEAR1;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_DISTGEAR1:                                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_DISTGEAR1;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TIMEGEAR1PER:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TIMEGEAR1PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_DISTGEAR1PER:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_DISTGEAR1PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TIMEGEAR2:                                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TIMEGEAR2;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_DISTGEAR2:                                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_DISTGEAR2;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TIMEGEAR2PER:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TIMEGEAR2PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_DISTGEAR2PER:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_DISTGEAR2PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TIMEGEAR3:                                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TIMEGEAR3;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_DISTGEAR3:                                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_DISTGEAR3;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TIMEGEAR3PER:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TIMEGEAR3PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_DISTGEAR3PER:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_DISTGEAR3PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TIMEGEAR4:                                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TIMEGEAR4;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_DISTGEAR4:                                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_DISTGEAR4;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TIMEGEAR4PER:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TIMEGEAR4PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_DISTGEAR4PER:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_DISTGEAR4PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TIMEGEAR5:                                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TIMEGEAR5;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_DISTGEAR5:                                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_DISTGEAR5;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TIMEGEAR5PER:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TIMEGEAR5PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_DISTGEAR5PER:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_DISTGEAR5PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TIMEGEAR6:                                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TIMEGEAR6;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_DISTGEAR6:                                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_DISTGEAR6;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TIMEGEAR6PER:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TIMEGEAR6PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_DISTGEAR6PER:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_DISTGEAR6PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_MOSTTIMEGEAR:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_MOSTTIMEGEAR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALDISTVALIDGEAR:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALDISTVALIDGEAR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALDISTWRONGGEAR:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALDISTWRONGGEAR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALDISTDOWNINDI:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALDISTDOWNINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALDISTUPINDI:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALDISTUPINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_AVGDISTWRONGINDI:                                       {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_AVGDISTWRONGINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_AVGDISTDOWNINDI:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_AVGDISTDOWNINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_AVGDISTUPINDI:                                          {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_AVGDISTUPINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALDISTWRONGGEARPER:                                  {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALDISTWRONGGEARPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALDISTDOWNINDIPER:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALDISTDOWNINDIPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALDISTUPINDIPER:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALDISTUPINDIPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALTIMEVALIDGEAR:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALTIMEVALIDGEAR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALTIMEWRONGGEAR:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALTIMEWRONGGEAR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALTIMEDOWNINDI:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALTIMEDOWNINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALTIMEUPINDI:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALTIMEUPINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALTIMEWRONGGEARPER:                                  {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALTIMEWRONGGEARPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALTIMEDOWNINDIPER:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALTIMEDOWNINDIPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALTIMEUPINDIPER:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALTIMEUPINDIPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALCOUNTWRONGGEAR:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALCOUNTWRONGGEAR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALCOUNTDOWNINDI:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALCOUNTDOWNINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALCOUNTUPINDI:                                       {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALCOUNTUPINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALCOUNTDOWNINDIPER:                                  {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALCOUNTDOWNINDIPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALCOUNTUPINDIPER:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALCOUNTUPINDIPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_AVGCOUNTUPINDI:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_AVGCOUNTUPINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_AVGCOUNTDOWNINDI:                                       {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_AVGCOUNTDOWNINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALTIMECORRECTGEARPER:                                {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALTIMECORRECTGEARPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_AVGGEARSHIFT:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_AVGGEARSHIFT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_NOOFGEARSHIFT:                                          {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_NOOFGEARSHIFT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_ODODISTPERTRIP:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_ODODISTPERTRIP;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOPSPEED:                                               {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TOPSPEED;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_DRIVEINSTRATING:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_DRIVEINSTRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_DRIVECUMURATING:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_DRIVECUMURATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_SPEEDBAND1TIME:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_SPEEDBAND1TIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_SPEEDBAND1TIMEPER:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_SPEEDBAND1TIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_SPEEDBAND2TIME:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_SPEEDBAND2TIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_SPEEDBAND2TIMEPER:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_SPEEDBAND2TIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_SPEEDBAND3TIME:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_SPEEDBAND3TIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_SPEEDBAND3TIMEPER:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_SPEEDBAND3TIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_SPEEDBAND4TIME:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_SPEEDBAND4TIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_SPEEDBAND4TIMEPER:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_SPEEDBAND4TIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TRIPDIST:                                               {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TRIPDIST;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TRIPDURATION:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TRIPDURATION;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_AVGSPEED:                                               {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_AVGSPEED;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_AVGFUELECO:                                             {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_AVGFUELECO;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_OVERALLINSTRATING:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_OVERALLINSTRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_OVERALLCUMURATING:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_OVERALLCUMURATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_PERTIMEWITHOUTSEATBELT:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_PERTIMEWITHOUTSEATBELT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_PERTIMEWITHSEATBELT:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_PERTIMEWITHSEATBELT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_SEATBELTFACTOR:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_SEATBELTFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_NOOFTIMEWITHOUTSEATBELT:                                {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_NOOFTIMEWITHOUTSEATBELT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_NOOFTIMEWITHSEATBELT:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_NOOFTIMEWITHSEATBELT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_NOOFTIMEWITHOUTSEATBELTPER:                             {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_NOOFTIMEWITHOUTSEATBELTPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_DOORCLOSETIMEPER:                                       {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_DOORCLOSETIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_DOOROPENTIMEPER:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_DOOROPENTIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TIMEHIGHSPEEDCLTBRKPRESSEDPER:                          {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TIMEHIGHSPEEDCLTBRKPRESSEDPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALTIMEHIGHSPEEDPER:                                  {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALTIMEHIGHSPEEDPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_SRSFACTOR:                                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_SRSFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TEABREAKFACTOR:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TEABREAKFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TRLFACTOR:                                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TRLFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TLLFACTOR:                                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TLLFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TBLFACTOR:                                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TBLFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TFLFACTOR:                                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TFLFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TPLFACTOR:                                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TPLFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TRVLFACTOR:                                             {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_TRVLFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_BRKFLDFACTOR:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_BRKFLDFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_OILPRFACTOR:                                            {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_OILPRFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_WIFFACTOR:                                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_WIFFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_VEHICLEHEALTH:                                          {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_VEHICLEHEALTH;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_SAFETYINSTRATING:                                       {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_SAFETYINSTRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_SAFETYCUMRATING:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TRIPB_SAFETYCUMRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_FUELECOINSTRATING:                                {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_FUELECOINSTRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_FUELECOCUMRATING:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_FUELECOCUMRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALTIME_ENGINEIDLE:                             {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALTIME_ENGINEIDLE;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_IDLETIME:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_IDLETIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_IDLETIMEPER:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_IDLETIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALFUELIDLE:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALFUELIDLE;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALTIME_RPMEFFINFO:                             {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALTIME_RPMEFFINFO;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALDIST:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALDIST;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_EFF_RPMTIMEAMBER:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_EFF_RPMTIMEAMBER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_EFF_RPMTIMEAMBERPER:                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_EFF_RPMTIMEAMBERPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_EFF_RPMTIMEGREEN:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_EFF_RPMTIMEGREEN;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_EFF_RPMTIMEGREENPER:                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_EFF_RPMTIMEGREENPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_EFF_RPMTIMERED:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_EFF_RPMTIMERED;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_EFF_RPMTIMEREDPER:                                {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_EFF_RPMTIMEREDPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_EFF_RPMDISTAMBER:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_EFF_RPMDISTAMBER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_EFF_RPMDISTAMBERPER:                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_EFF_RPMDISTAMBERPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_EFF_RPMDISTGREEN:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_EFF_RPMDISTGREEN;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_EFF_RPMDISTGREENPER:                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_EFF_RPMDISTGREENPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_EFF_RPMDISTRED:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_EFF_RPMDISTRED;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_EFF_RPMDISTREDPER:                                {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_EFF_RPMDISTREDPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_AVGENG_RPM:                                       {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_AVGENG_RPM;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALTIME_ACON:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALTIME_ACON;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_AC_ONTIME:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_AC_ONTIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_AC_ONTIMEPER:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_AC_ONTIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALTIME_CLT_ACC:                                {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALTIME_CLT_ACC;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_CLT_ACCTIME:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_CLT_ACCTIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_CLT_ACCTIMEPER:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_CLT_ACCTIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_BRKINSTRATING:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_BRKINSTRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_ACCLN:                                            {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_ACCLN;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_NOOFBRKCYCLE:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_NOOFBRKCYCLE;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_BRKCUMRATING:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_BRKCUMRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALBRK:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALBRK;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_NORMALBRK:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_NORMALBRK;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_NORMALBRKPER:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_NORMALBRKPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_MODERATEBRK:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_MODERATEBRK;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_MODERATEBRKPER:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_MODERATEBRKPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_HEAVYBRK:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_HEAVYBRK;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_HEAVYBRKPER:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_HEAVYBRKPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_PANICBRK:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_PANICBRK;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_PANICBRKPER:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_PANICBRKPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_HARSHBRK:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_HARSHBRK;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_HARSHBRKPER:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_HARSHBRKPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_AVGBRKCOUNT:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_AVGBRKCOUNT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_ODODISTPERTRIP_BRAKING:                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_ODODISTPERTRIP_BRAKING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_ACCINSTRATING:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_ACCINSTRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_ACCCUMRATING:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_ACCCUMRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALTRAVELTIME:                                  {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALTRAVELTIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALACCPEDALPRESSTIME:                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALACCPEDALPRESSTIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_ACCPEDALPRESSRANGE1:                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_ACCPEDALPRESSRANGE1;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_ACCPEDALPRESSRANGE1PER:                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_ACCPEDALPRESSRANGE1PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_ACCPEDALPRESSRANGE2:                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_ACCPEDALPRESSRANGE2;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_ACCPEDALPRESSRANGE2PER:                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_ACCPEDALPRESSRANGE2PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_ACCPEDALPRESSRANGE3:                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_ACCPEDALPRESSRANGE3;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_ACCPEDALPRESSRANGE3PER:                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_ACCPEDALPRESSRANGE3PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_ACCPEDALPRESSRANGE4:                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_ACCPEDALPRESSRANGE4;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_ACCPEDALPRESSRANGE4PER:                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_ACCPEDALPRESSRANGE4PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_ACCPEDALPRESSNO:                                  {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_ACCPEDALPRESSNO;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_ACCPEDALPRESNOPER:                                {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_ACCPEDALPRESNOPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_AVGACCPEDALPOS:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_AVGACCPEDALPOS;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_ACCHARSHCOUNT:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_ACCHARSHCOUNT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_VEHICLE_TXMNVARIANT:                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_VEHICLE_TXMNVARIANT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_GSINSTRATING:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_GSINSTRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_GSCUMRATING:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_GSCUMRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALDISTVALIDGEAR_GEARSHIFT:                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALDISTVALIDGEAR_GEARSHIFT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALTIMEVALIDGEAR_GEARSHIFT:                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALTIMEVALIDGEAR_GEARSHIFT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TIMEGEAR1:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TIMEGEAR1;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_DISTGEAR1:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_DISTGEAR1;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TIMEGEAR1PER:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TIMEGEAR1PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_DISTGEAR1PER:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_DISTGEAR1PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TIMEGEAR2:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TIMEGEAR2;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_DISTGEAR2:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_DISTGEAR2;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TIMEGEAR2PER:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TIMEGEAR2PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_DISTGEAR2PER:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_DISTGEAR2PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TIMEGEAR3:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TIMEGEAR3;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_DISTGEAR3:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_DISTGEAR3;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TIMEGEAR3PER:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TIMEGEAR3PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_DISTGEAR3PER:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_DISTGEAR3PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TIMEGEAR4:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TIMEGEAR4;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_DISTGEAR4:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_DISTGEAR4;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TIMEGEAR4PER:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TIMEGEAR4PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_DISTGEAR4PER:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_DISTGEAR4PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TIMEGEAR5:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TIMEGEAR5;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_DISTGEAR5:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_DISTGEAR5;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TIMEGEAR5PER:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TIMEGEAR5PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_DISTGEAR5PER:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_DISTGEAR5PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TIMEGEAR6:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TIMEGEAR6;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_DISTGEAR6:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_DISTGEAR6;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TIMEGEAR6PER:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TIMEGEAR6PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_DISTGEAR6PER:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_DISTGEAR6PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_MOSTTIMEGEAR:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_MOSTTIMEGEAR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALDISTVALIDGEAR:                               {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALDISTVALIDGEAR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALDISTWRONGGEAR:                               {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALDISTWRONGGEAR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALDISTDOWNINDI:                                {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALDISTDOWNINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALDISTUPINDI:                                  {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALDISTUPINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_AVGDISTWRONGINDI:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_AVGDISTWRONGINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_AVGDISTDOWNINDI:                                  {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_AVGDISTDOWNINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_AVGDISTUPINDI:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_AVGDISTUPINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALDISTWRONGGEARPER:                            {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALDISTWRONGGEARPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALDISTDOWNINDIPER:                             {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALDISTDOWNINDIPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALDISTUPINDIPER:                               {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALDISTUPINDIPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALTIMEVALIDGEAR:                               {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALTIMEVALIDGEAR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALTIMEWRONGGEAR:                               {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALTIMEWRONGGEAR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALTIMEDOWNINDI:                                {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALTIMEDOWNINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALTIMEUPINDI:                                  {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALTIMEUPINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALTIMEWRONGGEARPER:                            {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALTIMEWRONGGEARPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALTIMEDOWNINDIPER:                             {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALTIMEDOWNINDIPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALTIMEUPINDIPER:                               {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALTIMEUPINDIPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALCOUNTWRONGGEAR:                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALCOUNTWRONGGEAR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALCOUNTDOWNINDI:                               {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALCOUNTDOWNINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALCOUNTUPINDI:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALCOUNTUPINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALCOUNTDOWNINDIPER:                            {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALCOUNTDOWNINDIPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALCOUNTUPINDIPER:                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALCOUNTUPINDIPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_AVGCOUNTUPINDI:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_AVGCOUNTUPINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_AVGCOUNTDOWNINDI:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_AVGCOUNTDOWNINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALTIMECORRECTGEARPER:                          {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALTIMECORRECTGEARPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_AVGGEARSHIFT:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_AVGGEARSHIFT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_NOOFGEARSHIFT:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_NOOFGEARSHIFT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_ODODISTPERTRIP:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_ODODISTPERTRIP;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOPSPEED:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOPSPEED;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_DRIVEINSTRATING:                                  {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_DRIVEINSTRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_DRIVECUMURATING:                                  {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_DRIVECUMURATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_SPEEDBAND1TIME:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_SPEEDBAND1TIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_SPEEDBAND1TIMEPER:                                {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_SPEEDBAND1TIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_SPEEDBAND2TIME:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_SPEEDBAND2TIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_SPEEDBAND2TIMEPER:                                {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_SPEEDBAND2TIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_SPEEDBAND3TIME:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_SPEEDBAND3TIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_SPEEDBAND3TIMEPER:                                {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_SPEEDBAND3TIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_SPEEDBAND4TIME:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_SPEEDBAND4TIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_SPEEDBAND4TIMEPER:                                {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_SPEEDBAND4TIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TRIPDIST:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TRIPDIST;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TRIPDURATION:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TRIPDURATION;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_AVGSPEED:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_AVGSPEED;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_AVGFUELECO:                                       {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_AVGFUELECO;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_OVERALLINSTRATING:                                {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_OVERALLINSTRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_OVERALLCUMURATING:                                {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_OVERALLCUMURATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_PERTIMEWITHOUTSEATBELT:                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_PERTIMEWITHOUTSEATBELT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_PERTIMEWITHSEATBELT:                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_PERTIMEWITHSEATBELT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_SEATBELTFACTOR:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_SEATBELTFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_NOOFTIMEWITHOUTSEATBELT:                          {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_NOOFTIMEWITHOUTSEATBELT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_NOOFTIMEWITHSEATBELT:                             {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_NOOFTIMEWITHSEATBELT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_NOOFTIMEWITHOUTSEATBELTPER:                       {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_NOOFTIMEWITHOUTSEATBELTPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_DOORCLOSETIMEPER:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_DOORCLOSETIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_DOOROPENTIMEPER:                                  {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_DOOROPENTIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TIMEHIGHSPEEDCLTBRKPRESSEDPER:                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TIMEHIGHSPEEDCLTBRKPRESSEDPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALTIMEHIGHSPEEDPER:                            {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALTIMEHIGHSPEEDPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_SRSFACTOR:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_SRSFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TEABREAKFACTOR:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TEABREAKFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TRLFACTOR:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TRLFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TLLFACTOR:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TLLFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TBLFACTOR:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TBLFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TFLFACTOR:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TFLFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TPLFACTOR:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TPLFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TRVLFACTOR:                                       {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TRVLFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_BRKFLDFACTOR:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_BRKFLDFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_OILPRFACTOR:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_OILPRFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_WIFFACTOR:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_WIFFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_VEHICLEHEALTH:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_VEHICLEHEALTH;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_SAFETYINSTRATING:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_SAFETYINSTRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_SAFETYCUMRATING:                                  {eProxyValue=driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_SAFETYCUMRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_FUELECOINSTRATING:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_FUELECOINSTRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_FUELECOCUMRATING:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_FUELECOCUMRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALTIME_ENGINEIDLE:                                {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALTIME_ENGINEIDLE;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_IDLETIME:                                            {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_IDLETIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_IDLETIMEPER:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_IDLETIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALFUELIDLE:                                       {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALFUELIDLE;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALTIME_RPMEFFINFO:                                {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALTIME_RPMEFFINFO;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALDIST:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALDIST;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_EFF_RPMTIMEAMBER:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_EFF_RPMTIMEAMBER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_EFF_RPMTIMEAMBERPER:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_EFF_RPMTIMEAMBERPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_EFF_RPMTIMEGREEN:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_EFF_RPMTIMEGREEN;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_EFF_RPMTIMEGREENPER:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_EFF_RPMTIMEGREENPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_EFF_RPMTIMERED:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_EFF_RPMTIMERED;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_EFF_RPMTIMEREDPER:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_EFF_RPMTIMEREDPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_EFF_RPMDISTAMBER:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_EFF_RPMDISTAMBER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_EFF_RPMDISTAMBERPER:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_EFF_RPMDISTAMBERPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_EFF_RPMDISTGREEN:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_EFF_RPMDISTGREEN;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_EFF_RPMDISTGREENPER:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_EFF_RPMDISTGREENPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_EFF_RPMDISTRED:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_EFF_RPMDISTRED;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_EFF_RPMDISTREDPER:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_EFF_RPMDISTREDPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_AVGENG_RPM:                                          {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_AVGENG_RPM;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALTIME_ACON:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALTIME_ACON;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_AC_ONTIME:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_AC_ONTIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_AC_ONTIMEPER:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_AC_ONTIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALTIME_CLT_ACC:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALTIME_CLT_ACC;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_CLT_ACCTIME:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_CLT_ACCTIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_CLT_ACCTIMEPER:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_CLT_ACCTIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_BRKINSTRATING:                                       {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_BRKINSTRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_ACCLN:                                               {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_ACCLN;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_NOOFBRKCYCLE:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_NOOFBRKCYCLE;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_BRKCUMRATING:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_BRKCUMRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALBRK:                                            {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALBRK;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_NORMALBRK:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_NORMALBRK;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_NORMALBRKPER:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_NORMALBRKPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_MODERATEBRK:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_MODERATEBRK;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_MODERATEBRKPER:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_MODERATEBRKPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_HEAVYBRK:                                            {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_HEAVYBRK;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_HEAVYBRKPER:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_HEAVYBRKPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_PANICBRK:                                            {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_PANICBRK;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_PANICBRKPER:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_PANICBRKPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_HARSHBRK:                                            {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_HARSHBRK;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_HARSHBRKPER:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_HARSHBRKPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_AVGBRKCOUNT:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_AVGBRKCOUNT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_ODODISTPERTRIP_BRAKING:                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_ODODISTPERTRIP_BRAKING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_ACCINSTRATING:                                       {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_ACCINSTRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_ACCCUMRATING:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_ACCCUMRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALTRAVELTIME:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALTRAVELTIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALACCPEDALPRESSTIME:                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALACCPEDALPRESSTIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_ACCPEDALPRESSRANGE1:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_ACCPEDALPRESSRANGE1;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_ACCPEDALPRESSRANGE1PER:                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_ACCPEDALPRESSRANGE1PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_ACCPEDALPRESSRANGE2:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_ACCPEDALPRESSRANGE2;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_ACCPEDALPRESSRANGE2PER:                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_ACCPEDALPRESSRANGE2PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_ACCPEDALPRESSRANGE3:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_ACCPEDALPRESSRANGE3;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_ACCPEDALPRESSRANGE3PER:                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_ACCPEDALPRESSRANGE3PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_ACCPEDALPRESSRANGE4:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_ACCPEDALPRESSRANGE4;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_ACCPEDALPRESSRANGE4PER:                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_ACCPEDALPRESSRANGE4PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_ACCPEDALPRESSNO:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_ACCPEDALPRESSNO;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_ACCPEDALPRESNOPER:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_ACCPEDALPRESNOPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_AVGACCPEDALPOS:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_AVGACCPEDALPOS;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_ACCHARSHCOUNT:                                       {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_ACCHARSHCOUNT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_VEHICLE_TXMNVARIANT:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_VEHICLE_TXMNVARIANT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_GSINSTRATING:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_GSINSTRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_GSCUMRATING:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_GSCUMRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALDISTVALIDGEAR_GEARSHIFT:                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALDISTVALIDGEAR_GEARSHIFT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALTIMEVALIDGEAR_GEARSHIFT:                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALTIMEVALIDGEAR_GEARSHIFT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TIMEGEAR1:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TIMEGEAR1;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_DISTGEAR1:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_DISTGEAR1;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TIMEGEAR1PER:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TIMEGEAR1PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_DISTGEAR1PER:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_DISTGEAR1PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TIMEGEAR2:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TIMEGEAR2;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_DISTGEAR2:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_DISTGEAR2;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TIMEGEAR2PER:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TIMEGEAR2PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_DISTGEAR2PER:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_DISTGEAR2PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TIMEGEAR3:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TIMEGEAR3;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_DISTGEAR3:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_DISTGEAR3;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TIMEGEAR3PER:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TIMEGEAR3PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_DISTGEAR3PER:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_DISTGEAR3PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TIMEGEAR4:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TIMEGEAR4;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_DISTGEAR4:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_DISTGEAR4;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TIMEGEAR4PER:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TIMEGEAR4PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_DISTGEAR4PER:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_DISTGEAR4PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TIMEGEAR5:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TIMEGEAR5;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_DISTGEAR5:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_DISTGEAR5;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TIMEGEAR5PER:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TIMEGEAR5PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_DISTGEAR5PER:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_DISTGEAR5PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TIMEGEAR6:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TIMEGEAR6;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_DISTGEAR6:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_DISTGEAR6;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TIMEGEAR6PER:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TIMEGEAR6PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_DISTGEAR6PER:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_DISTGEAR6PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_MOSTTIMEGEAR:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_MOSTTIMEGEAR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALDISTVALIDGEAR:                                  {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALDISTVALIDGEAR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALDISTWRONGGEAR:                                  {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALDISTWRONGGEAR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALDISTDOWNINDI:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALDISTDOWNINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALDISTUPINDI:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALDISTUPINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_AVGDISTWRONGINDI:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_AVGDISTWRONGINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_AVGDISTDOWNINDI:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_AVGDISTDOWNINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_AVGDISTUPINDI:                                       {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_AVGDISTUPINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALDISTWRONGGEARPER:                               {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALDISTWRONGGEARPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALDISTDOWNINDIPER:                                {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALDISTDOWNINDIPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALDISTUPINDIPER:                                  {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALDISTUPINDIPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALTIMEVALIDGEAR:                                  {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALTIMEVALIDGEAR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALTIMEWRONGGEAR:                                  {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALTIMEWRONGGEAR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALTIMEDOWNINDI:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALTIMEDOWNINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALTIMEUPINDI:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALTIMEUPINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALTIMEWRONGGEARPER:                               {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALTIMEWRONGGEARPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALTIMEDOWNINDIPER:                                {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALTIMEDOWNINDIPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALTIMEUPINDIPER:                                  {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALTIMEUPINDIPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALCOUNTWRONGGEAR:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALCOUNTWRONGGEAR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALCOUNTDOWNINDI:                                  {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALCOUNTDOWNINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALCOUNTUPINDI:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALCOUNTUPINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALCOUNTDOWNINDIPER:                               {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALCOUNTDOWNINDIPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALCOUNTUPINDIPER:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALCOUNTUPINDIPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_AVGCOUNTUPINDI:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_AVGCOUNTUPINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_AVGCOUNTDOWNINDI:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_AVGCOUNTDOWNINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALTIMECORRECTGEARPER:                             {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALTIMECORRECTGEARPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_AVGGEARSHIFT:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_AVGGEARSHIFT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_NOOFGEARSHIFT:                                       {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_NOOFGEARSHIFT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_ODODISTPERTRIP:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_ODODISTPERTRIP;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOPSPEED:                                            {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOPSPEED;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_DRIVEINSTRATING:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_DRIVEINSTRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_DRIVECUMURATING:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_DRIVECUMURATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_SPEEDBAND1TIME:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_SPEEDBAND1TIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_SPEEDBAND1TIMEPER:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_SPEEDBAND1TIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_SPEEDBAND2TIME:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_SPEEDBAND2TIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_SPEEDBAND2TIMEPER:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_SPEEDBAND2TIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_SPEEDBAND3TIME:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_SPEEDBAND3TIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_SPEEDBAND3TIMEPER:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_SPEEDBAND3TIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_SPEEDBAND4TIME:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_SPEEDBAND4TIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_SPEEDBAND4TIMEPER:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_SPEEDBAND4TIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TRIPDIST:                                            {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TRIPDIST;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TRIPDURATION:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TRIPDURATION;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_AVGSPEED:                                            {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_AVGSPEED;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_AVGFUELECO:                                          {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_AVGFUELECO;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_OVERALLINSTRATING:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_OVERALLINSTRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_OVERALLCUMURATING:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_OVERALLCUMURATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_PERTIMEWITHOUTSEATBELT:                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_PERTIMEWITHOUTSEATBELT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_PERTIMEWITHSEATBELT:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_PERTIMEWITHSEATBELT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_SEATBELTFACTOR:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_SEATBELTFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_NOOFTIMEWITHOUTSEATBELT:                             {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_NOOFTIMEWITHOUTSEATBELT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_NOOFTIMEWITHSEATBELT:                                {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_NOOFTIMEWITHSEATBELT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_NOOFTIMEWITHOUTSEATBELTPER:                          {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_NOOFTIMEWITHOUTSEATBELTPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_DOORCLOSETIMEPER:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_DOORCLOSETIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_DOOROPENTIMEPER:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_DOOROPENTIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TIMEHIGHSPEEDCLTBRKPRESSEDPER:                       {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TIMEHIGHSPEEDCLTBRKPRESSEDPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALTIMEHIGHSPEEDPER:                               {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALTIMEHIGHSPEEDPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_SRSFACTOR:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_SRSFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TEABREAKFACTOR:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TEABREAKFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TRLFACTOR:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TRLFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TLLFACTOR:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TLLFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TBLFACTOR:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TBLFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TFLFACTOR:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TFLFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TPLFACTOR:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TPLFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TRVLFACTOR:                                          {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TRVLFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_BRKFLDFACTOR:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_BRKFLDFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_OILPRFACTOR:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_OILPRFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_WIFFACTOR:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_WIFFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_VEHICLEHEALTH:                                       {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_VEHICLEHEALTH;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_SAFETYINSTRATING:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_SAFETYINSTRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_SAFETYCUMRATING:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::BESTTRIP_SAFETYCUMRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_FUELECOINSTRATING:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_FUELECOINSTRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_FUELECOCUMRATING:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_FUELECOCUMRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALTIME_ENGINEIDLE:                                {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALTIME_ENGINEIDLE;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_IDLETIME:                                            {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_IDLETIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_IDLETIMEPER:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_IDLETIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALFUELIDLE:                                       {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALFUELIDLE;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALTIME_RPMEFFINFO:                                {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALTIME_RPMEFFINFO;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALDIST:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALDIST;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_EFF_RPMTIMEAMBER:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_EFF_RPMTIMEAMBER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_EFF_RPMTIMEAMBERPER:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_EFF_RPMTIMEAMBERPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_EFF_RPMTIMEGREEN:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_EFF_RPMTIMEGREEN;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_EFF_RPMTIMEGREENPER:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_EFF_RPMTIMEGREENPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_EFF_RPMTIMERED:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_EFF_RPMTIMERED;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_EFF_RPMTIMEREDPER:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_EFF_RPMTIMEREDPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_EFF_RPMDISTAMBER:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_EFF_RPMDISTAMBER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_EFF_RPMDISTAMBERPER:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_EFF_RPMDISTAMBERPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_EFF_RPMDISTGREEN:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_EFF_RPMDISTGREEN;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_EFF_RPMDISTGREENPER:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_EFF_RPMDISTGREENPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_EFF_RPMDISTRED:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_EFF_RPMDISTRED;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_EFF_RPMDISTREDPER:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_EFF_RPMDISTREDPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_AVGENG_RPM:                                          {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_AVGENG_RPM;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALTIME_ACON:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALTIME_ACON;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_AC_ONTIME:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_AC_ONTIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_AC_ONTIMEPER:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_AC_ONTIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALTIME_CLT_ACC:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALTIME_CLT_ACC;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_CLT_ACCTIME:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_CLT_ACCTIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_CLT_ACCTIMEPER:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_CLT_ACCTIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_BRKINSTRATING:                                       {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_BRKINSTRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_ACCLN:                                               {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_ACCLN;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_NOOFBRKCYCLE:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_NOOFBRKCYCLE;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_BRKCUMRATING:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_BRKCUMRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALBRK:                                            {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALBRK;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_NORMALBRK:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_NORMALBRK;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_NORMALBRKPER:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_NORMALBRKPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_MODERATEBRK:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_MODERATEBRK;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_MODERATEBRKPER:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_MODERATEBRKPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_HEAVYBRK:                                            {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_HEAVYBRK;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_HEAVYBRKPER:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_HEAVYBRKPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_PANICBRK:                                            {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_PANICBRK;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_PANICBRKPER:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_PANICBRKPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_HARSHBRK:                                            {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_HARSHBRK;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_HARSHBRKPER:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_HARSHBRKPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_AVGBRKCOUNT:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_AVGBRKCOUNT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_ODODISTPERTRIP_BRAKING:                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_ODODISTPERTRIP_BRAKING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_ACCINSTRATING:                                       {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_ACCINSTRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_ACCCUMRATING:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_ACCCUMRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALTRAVELTIME:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALTRAVELTIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALACCPEDALPRESSTIME:                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALACCPEDALPRESSTIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_ACCPEDALPRESSRANGE1:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_ACCPEDALPRESSRANGE1;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_ACCPEDALPRESSRANGE1PER:                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_ACCPEDALPRESSRANGE1PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_ACCPEDALPRESSRANGE2:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_ACCPEDALPRESSRANGE2;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_ACCPEDALPRESSRANGE2PER:                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_ACCPEDALPRESSRANGE2PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_ACCPEDALPRESSRANGE3:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_ACCPEDALPRESSRANGE3;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_ACCPEDALPRESSRANGE3PER:                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_ACCPEDALPRESSRANGE3PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_ACCPEDALPRESSRANGE4:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_ACCPEDALPRESSRANGE4;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_ACCPEDALPRESSRANGE4PER:                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_ACCPEDALPRESSRANGE4PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_ACCPEDALPRESSNO:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_ACCPEDALPRESSNO;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_ACCPEDALPRESNOPER:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_ACCPEDALPRESNOPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_AVGACCPEDALPOS:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_AVGACCPEDALPOS;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_ACCHARSHCOUNT:                                       {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_ACCHARSHCOUNT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_VEHICLE_TXMNVARIANT:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_VEHICLE_TXMNVARIANT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_GSINSTRATING:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_GSINSTRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_GSCUMRATING:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_GSCUMRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALDISTVALIDGEAR_GEARSHIFT:                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALDISTVALIDGEAR_GEARSHIFT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALTIMEVALIDGEAR_GEARSHIFT:                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALTIMEVALIDGEAR_GEARSHIFT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TIMEGEAR1:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TIMEGEAR1;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_DISTGEAR1:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_DISTGEAR1;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TIMEGEAR1PER:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TIMEGEAR1PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_DISTGEAR1PER:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_DISTGEAR1PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TIMEGEAR2:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TIMEGEAR2;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_DISTGEAR2:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_DISTGEAR2;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TIMEGEAR2PER:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TIMEGEAR2PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_DISTGEAR2PER:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_DISTGEAR2PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TIMEGEAR3:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TIMEGEAR3;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_DISTGEAR3:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_DISTGEAR3;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TIMEGEAR3PER:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TIMEGEAR3PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_DISTGEAR3PER:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_DISTGEAR3PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TIMEGEAR4:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TIMEGEAR4;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_DISTGEAR4:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_DISTGEAR4;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TIMEGEAR4PER:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TIMEGEAR4PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_DISTGEAR4PER:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_DISTGEAR4PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TIMEGEAR5:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TIMEGEAR5;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_DISTGEAR5:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_DISTGEAR5;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TIMEGEAR5PER:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TIMEGEAR5PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_DISTGEAR5PER:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_DISTGEAR5PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TIMEGEAR6:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TIMEGEAR6;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_DISTGEAR6:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_DISTGEAR6;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TIMEGEAR6PER:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TIMEGEAR6PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_DISTGEAR6PER:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_DISTGEAR6PER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_MOSTTIMEGEAR:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_MOSTTIMEGEAR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALDISTVALIDGEAR:                                  {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALDISTVALIDGEAR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALDISTWRONGGEAR:                                  {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALDISTWRONGGEAR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALDISTDOWNINDI:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALDISTDOWNINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALDISTUPINDI:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALDISTUPINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_AVGDISTWRONGINDI:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_AVGDISTWRONGINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_AVGDISTDOWNINDI:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_AVGDISTDOWNINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_AVGDISTUPINDI:                                       {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_AVGDISTUPINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALDISTWRONGGEARPER:                               {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALDISTWRONGGEARPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALDISTDOWNINDIPER:                                {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALDISTDOWNINDIPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALDISTUPINDIPER:                                  {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALDISTUPINDIPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALTIMEVALIDGEAR:                                  {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALTIMEVALIDGEAR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALTIMEWRONGGEAR:                                  {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALTIMEWRONGGEAR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALTIMEDOWNINDI:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALTIMEDOWNINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALTIMEUPINDI:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALTIMEUPINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALTIMEWRONGGEARPER:                               {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALTIMEWRONGGEARPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALTIMEDOWNINDIPER:                                {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALTIMEDOWNINDIPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALTIMEUPINDIPER:                                  {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALTIMEUPINDIPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALCOUNTWRONGGEAR:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALCOUNTWRONGGEAR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALCOUNTDOWNINDI:                                  {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALCOUNTDOWNINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALCOUNTUPINDI:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALCOUNTUPINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALCOUNTDOWNINDIPER:                               {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALCOUNTDOWNINDIPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALCOUNTUPINDIPER:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALCOUNTUPINDIPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_AVGCOUNTUPINDI:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_AVGCOUNTUPINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_AVGCOUNTDOWNINDI:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_AVGCOUNTDOWNINDI;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALTIMECORRECTGEARPER:                             {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALTIMECORRECTGEARPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_AVGGEARSHIFT:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_AVGGEARSHIFT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_NOOFGEARSHIFT:                                       {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_NOOFGEARSHIFT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_ODODISTPERTRIP:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_ODODISTPERTRIP;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOPSPEED:                                            {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOPSPEED;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_DRIVEINSTRATING:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_DRIVEINSTRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_DRIVECUMURATING:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_DRIVECUMURATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_SPEEDBAND1TIME:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_SPEEDBAND1TIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_SPEEDBAND1TIMEPER:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_SPEEDBAND1TIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_SPEEDBAND2TIME:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_SPEEDBAND2TIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_SPEEDBAND2TIMEPER:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_SPEEDBAND2TIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_SPEEDBAND3TIME:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_SPEEDBAND3TIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_SPEEDBAND3TIMEPER:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_SPEEDBAND3TIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_SPEEDBAND4TIME:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_SPEEDBAND4TIME;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_SPEEDBAND4TIMEPER:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_SPEEDBAND4TIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TRIPDIST:                                            {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TRIPDIST;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TRIPDURATION:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TRIPDURATION;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_AVGSPEED:                                            {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_AVGSPEED;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_AVGFUELECO:                                          {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_AVGFUELECO;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_OVERALLINSTRATING:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_OVERALLINSTRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_OVERALLCUMURATING:                                   {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_OVERALLCUMURATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_PERTIMEWITHOUTSEATBELT:                              {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_PERTIMEWITHOUTSEATBELT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_PERTIMEWITHSEATBELT:                                 {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_PERTIMEWITHSEATBELT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_SEATBELTFACTOR:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_SEATBELTFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_NOOFTIMEWITHOUTSEATBELT:                             {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_NOOFTIMEWITHOUTSEATBELT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_NOOFTIMEWITHSEATBELT:                                {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_NOOFTIMEWITHSEATBELT;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_NOOFTIMEWITHOUTSEATBELTPER:                          {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_NOOFTIMEWITHOUTSEATBELTPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_DOORCLOSETIMEPER:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_DOORCLOSETIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_DOOROPENTIMEPER:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_DOOROPENTIMEPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TIMEHIGHSPEEDCLTBRKPRESSEDPER:                       {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TIMEHIGHSPEEDCLTBRKPRESSEDPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALTIMEHIGHSPEEDPER:                               {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALTIMEHIGHSPEEDPER;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_SRSFACTOR:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_SRSFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TEABREAKFACTOR:                                      {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TEABREAKFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TRLFACTOR:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TRLFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TLLFACTOR:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TLLFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TBLFACTOR:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TBLFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TFLFACTOR:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TFLFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TPLFACTOR:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TPLFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TRVLFACTOR:                                          {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TRVLFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_BRKFLDFACTOR:                                        {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_BRKFLDFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_OILPRFACTOR:                                         {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_OILPRFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_WIFFACTOR:                                           {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_WIFFACTOR;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_VEHICLEHEALTH:                                       {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_VEHICLEHEALTH;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_SAFETYINSTRATING:                                    {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_SAFETYINSTRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_SAFETYCUMRATING:                                     {eProxyValue=driveProTypeCollection::eSignalNames::Literal::LASTTRIP_SAFETYCUMRATING;}break;
    case EDriveNextSignalTypes::DRIVENEXT_SIG_TOTAL_COUNT:                                                  {eProxyValue=driveProTypeCollection::eSignalNames::Literal::TOTAL_COUNT;}break;
    default:
    {
        //eProxyValue=driveProTypeCollection::eSignalNames::Literal::UNKONWN;
        LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, eHmiValue:%d, eProxyValue:%d", __FUNCTION__, static_cast<int>(eHmiValue), static_cast<int>(eProxyValue));
    }
        break;
    }
    return eProxyValue;
}

EDriveNextSignalTypes CDriveNextModerator::convertToDNHmiSignalEnumValue(driveProTypeCollection::eSignalNames::Literal eProxyValue)
{
    EDriveNextSignalTypes eHmiValue = EDriveNextSignalTypes::DRIVENEXT_SIG_UNKNOWN;
    switch(eProxyValue)
    {
    case driveProTypeCollection::eSignalNames::Literal::UNKONWN:                                                    {/*eHmiValue = EDriveNextSignalTypes::DRIVENEXT_SIG_UNKNOWN;*/}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_FUELECOINSTRATING:                              {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_FUELECOINSTRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_FUELECOCUMRATING:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_FUELECOCUMRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALTIME_ENGINEIDLE:                           {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIME_ENGINEIDLE;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_IDLETIME:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_IDLETIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_IDLETIMEPER:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_IDLETIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALFUELIDLE:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALFUELIDLE;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALTIME_RPMEFFINFO:                           {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIME_RPMEFFINFO;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALDIST:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALDIST;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_EFF_RPMTIMEAMBER:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMTIMEAMBER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_EFF_RPMTIMEAMBERPER:                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMTIMEAMBERPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_EFF_RPMTIMEGREEN:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMTIMEGREEN;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_EFF_RPMTIMEGREENPER:                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMTIMEGREENPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_EFF_RPMTIMERED:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMTIMERED;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_EFF_RPMTIMEREDPER:                              {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMTIMEREDPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_EFF_RPMDISTAMBER:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMDISTAMBER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_EFF_RPMDISTAMBERPER:                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMDISTAMBERPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_EFF_RPMDISTGREEN:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMDISTGREEN;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_EFF_RPMDISTGREENPER:                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMDISTGREENPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_EFF_RPMDISTRED:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMDISTRED;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_EFF_RPMDISTREDPER:                              {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMDISTREDPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_AVGENG_RPM:                                     {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGENG_RPM;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALTIME_ACON:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIME_ACON;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_AC_ONTIME:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AC_ONTIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_AC_ONTIMEPER:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AC_ONTIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALTIME_CLT_ACC:                              {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIME_CLT_ACC;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_CLT_ACCTIME:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_CLT_ACCTIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_CLT_ACCTIMEPER:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_CLT_ACCTIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_BRKINSTRATING:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_BRKINSTRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_ACCLN:                                          {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCLN;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_NOOFBRKCYCLE:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_NOOFBRKCYCLE;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_BRKCUMRATING:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_BRKCUMRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALBRK:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALBRK;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_NORMALBRK:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_NORMALBRK;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_NORMALBRKPER:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_NORMALBRKPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_MODERATEBRK:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_MODERATEBRK;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_MODERATEBRKPER:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_MODERATEBRKPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_HEAVYBRK:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_HEAVYBRK;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_HEAVYBRKPER:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_HEAVYBRKPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_PANICBRK:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_PANICBRK;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_PANICBRKPER:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_PANICBRKPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_HARSHBRK:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_HARSHBRK;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_HARSHBRKPER:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_HARSHBRKPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_AVGBRKCOUNT:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGBRKCOUNT;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_ODODISTPERTRIP_BRAKING:                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ODODISTPERTRIP_BRAKING;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_ACCINSTRATING:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCINSTRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_ACCCUMRATING:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCCUMRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALTRAVELTIME:                                {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTRAVELTIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALACCPEDALPRESSTIME:                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALACCPEDALPRESSTIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_ACCPEDALPRESSRANGE1:                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCPEDALPRESSRANGE1;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_ACCPEDALPRESSRANGE1PER:                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCPEDALPRESSRANGE1PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_ACCPEDALPRESSRANGE2:                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCPEDALPRESSRANGE2;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_ACCPEDALPRESSRANGE2PER:                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCPEDALPRESSRANGE2PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_ACCPEDALPRESSRANGE3:                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCPEDALPRESSRANGE3;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_ACCPEDALPRESSRANGE3PER:                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCPEDALPRESSRANGE3PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_ACCPEDALPRESSRANGE4:                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCPEDALPRESSRANGE4;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_ACCPEDALPRESSRANGE4PER:                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCPEDALPRESSRANGE4PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_ACCPEDALPRESSNO:                                {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCPEDALPRESSNO;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_ACCPEDALPRESNOPER:                              {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCPEDALPRESNOPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_AVGACCPEDALPOS:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGACCPEDALPOS;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_ACCHARSHCOUNT:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCHARSHCOUNT;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_VEHICLE_TXMNVARIANT:                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_VEHICLE_TXMNVARIANT;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_GSINSTRATING:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_GSINSTRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_GSCUMRATING:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_GSCUMRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALDISTVALIDGEAR_GEARSHIFT:                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALDISTVALIDGEAR_GEARSHIFT;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALTIMEVALIDGEAR_GEARSHIFT:                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIMEVALIDGEAR_GEARSHIFT;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TIMEGEAR1:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR1;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_DISTGEAR1:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR1;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TIMEGEAR1PER:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR1PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_DISTGEAR1PER:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR1PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TIMEGEAR2:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR2;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_DISTGEAR2:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR2;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TIMEGEAR2PER:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR2PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_DISTGEAR2PER:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR2PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TIMEGEAR3:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR3;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_DISTGEAR3:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR3;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TIMEGEAR3PER:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR3PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_DISTGEAR3PER:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR3PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TIMEGEAR4:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR4;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_DISTGEAR4:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR4;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TIMEGEAR4PER:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR4PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_DISTGEAR4PER:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR4PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TIMEGEAR5:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR5;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_DISTGEAR5:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR5;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TIMEGEAR5PER:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR5PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_DISTGEAR5PER:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR5PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TIMEGEAR6:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR6;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_DISTGEAR6:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR6;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TIMEGEAR6PER:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR6PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_DISTGEAR6PER:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR6PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_MOSTTIMEGEAR:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_MOSTTIMEGEAR;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALDISTVALIDGEAR:                             {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALDISTVALIDGEAR;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALDISTWRONGGEAR:                             {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALDISTWRONGGEAR;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALDISTDOWNINDI:                              {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALDISTDOWNINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALDISTUPINDI:                                {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALDISTUPINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_AVGDISTWRONGINDI:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGDISTWRONGINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_AVGDISTDOWNINDI:                                {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGDISTDOWNINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_AVGDISTUPINDI:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGDISTUPINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALDISTWRONGGEARPER:                          {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALDISTWRONGGEARPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALDISTDOWNINDIPER:                           {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALDISTDOWNINDIPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALDISTUPINDIPER:                             {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALDISTUPINDIPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALTIMEVALIDGEAR:                             {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIMEVALIDGEAR;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALTIMEWRONGGEAR:                             {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIMEWRONGGEAR;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALTIMEDOWNINDI:                              {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIMEDOWNINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALTIMEUPINDI:                                {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIMEUPINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALTIMEWRONGGEARPER:                          {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIMEWRONGGEARPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALTIMEDOWNINDIPER:                           {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIMEDOWNINDIPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALTIMEUPINDIPER:                             {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIMEUPINDIPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALCOUNTWRONGGEAR:                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALCOUNTWRONGGEAR;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALCOUNTDOWNINDI:                             {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALCOUNTDOWNINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALCOUNTUPINDI:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALCOUNTUPINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALCOUNTDOWNINDIPER:                          {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALCOUNTDOWNINDIPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALCOUNTUPINDIPER:                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALCOUNTUPINDIPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_AVGCOUNTUPINDI:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGCOUNTUPINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_AVGCOUNTDOWNINDI:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGCOUNTDOWNINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALTIMECORRECTGEARPER:                        {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIMECORRECTGEARPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_AVGGEARSHIFT:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGGEARSHIFT;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_NOOFGEARSHIFT:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_NOOFGEARSHIFT;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_ODODISTPERTRIP:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ODODISTPERTRIP;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOPSPEED:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOPSPEED;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_DRIVEINSTRATING:                                {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DRIVEINSTRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_DRIVECUMURATING:                                {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DRIVECUMURATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_SPEEDBAND1TIME:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SPEEDBAND1TIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_SPEEDBAND1TIMEPER:                              {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SPEEDBAND1TIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_SPEEDBAND2TIME:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SPEEDBAND2TIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_SPEEDBAND2TIMEPER:                              {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SPEEDBAND2TIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_SPEEDBAND3TIME:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SPEEDBAND3TIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_SPEEDBAND3TIMEPER:                              {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SPEEDBAND3TIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_SPEEDBAND4TIME:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SPEEDBAND4TIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_SPEEDBAND4TIMEPER:                              {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SPEEDBAND4TIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TRIPDIST:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TRIPDIST;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TRIPDURATION:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TRIPDURATION;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_AVGSPEED:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGSPEED;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_AVGFUELECO:                                     {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGFUELECO;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_OVERALLINSTRATING:                              {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_OVERALLINSTRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_OVERALLCUMURATING:                              {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_OVERALLCUMURATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_PERTIMEWITHOUTSEATBELT:                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_PERTIMEWITHOUTSEATBELT;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_PERTIMEWITHSEATBELT:                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_PERTIMEWITHSEATBELT;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_SEATBELTFACTOR:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SEATBELTFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_NOOFTIMEWITHOUTSEATBELT:                        {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_NOOFTIMEWITHOUTSEATBELT;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_NOOFTIMEWITHSEATBELT:                           {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_NOOFTIMEWITHSEATBELT;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_NOOFTIMEWITHOUTSEATBELTPER:                     {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_NOOFTIMEWITHOUTSEATBELTPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_DOORCLOSETIMEPER:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DOORCLOSETIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_DOOROPENTIMEPER:                                {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DOOROPENTIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TIMEHIGHSPEEDCLTBRKPRESSEDPER:                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEHIGHSPEEDCLTBRKPRESSEDPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TOTALTIMEHIGHSPEEDPER:                          {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIMEHIGHSPEEDPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_SRSFACTOR:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SRSFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TEABREAKFACTOR:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TEABREAKFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TRLFACTOR:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TRLFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TLLFACTOR:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TLLFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TBLFACTOR:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TBLFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TFLFACTOR:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TFLFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TPLFACTOR:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TPLFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_TRVLFACTOR:                                     {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TRVLFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_BRKFLDFACTOR:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_BRKFLDFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_OILPRFACTOR:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_OILPRFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_WIFFACTOR:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_WIFFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_VEHICLEHEALTH:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_VEHICLEHEALTH;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_SAFETYINSTRATING:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SAFETYINSTRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::CURRENTTRIP_SAFETYCUMRATING:                                {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SAFETYCUMRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_FUELECOINSTRATING:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_FUELECOINSTRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_FUELECOCUMRATING:                                     {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_FUELECOCUMRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALTIME_ENGINEIDLE:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALTIME_ENGINEIDLE;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_IDLETIME:                                             {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_IDLETIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_IDLETIMEPER:                                          {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_IDLETIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALFUELIDLE:                                        {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALFUELIDLE;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALTIME_RPMEFFINFO:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALTIME_RPMEFFINFO;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALDIST:                                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALDIST;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_EFF_RPMTIMEAMBER:                                     {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_EFF_RPMTIMEAMBER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_EFF_RPMTIMEAMBERPER:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_EFF_RPMTIMEAMBERPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_EFF_RPMTIMEGREEN:                                     {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_EFF_RPMTIMEGREEN;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_EFF_RPMTIMEGREENPER:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_EFF_RPMTIMEGREENPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_EFF_RPMTIMERED:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_EFF_RPMTIMERED;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_EFF_RPMTIMEREDPER:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_EFF_RPMTIMEREDPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_EFF_RPMDISTAMBER:                                     {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_EFF_RPMDISTAMBER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_EFF_RPMDISTAMBERPER:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_EFF_RPMDISTAMBERPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_EFF_RPMDISTGREEN:                                     {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_EFF_RPMDISTGREEN;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_EFF_RPMDISTGREENPER:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_EFF_RPMDISTGREENPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_EFF_RPMDISTRED:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_EFF_RPMDISTRED;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_EFF_RPMDISTREDPER:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_EFF_RPMDISTREDPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_AVGENG_RPM:                                           {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_AVGENG_RPM;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALTIME_ACON:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALTIME_ACON;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_AC_ONTIME:                                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_AC_ONTIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_AC_ONTIMEPER:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_AC_ONTIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALTIME_CLT_ACC:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALTIME_CLT_ACC;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_CLT_ACCTIME:                                          {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_CLT_ACCTIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_CLT_ACCTIMEPER:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_CLT_ACCTIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_BRKINSTRATING:                                        {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_BRKINSTRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_ACCLN:                                                {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_ACCLN;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_NOOFBRKCYCLE:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_NOOFBRKCYCLE;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_BRKCUMRATING:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_BRKCUMRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALBRK:                                             {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALBRK;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_NORMALBRK:                                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_NORMALBRK;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_NORMALBRKPER:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_NORMALBRKPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_MODERATEBRK:                                          {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_MODERATEBRK;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_MODERATEBRKPER:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_MODERATEBRKPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_HEAVYBRK:                                             {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_HEAVYBRK;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_HEAVYBRKPER:                                          {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_HEAVYBRKPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_PANICBRK:                                             {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_PANICBRK;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_PANICBRKPER:                                          {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_PANICBRKPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_HARSHBRK:                                             {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_HARSHBRK;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_HARSHBRKPER:                                          {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_HARSHBRKPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_AVGBRKCOUNT:                                          {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_AVGBRKCOUNT;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_ODODISTPERTRIP_BRAKING:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_ODODISTPERTRIP_BRAKING;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_ACCINSTRATING:                                        {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_ACCINSTRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_ACCCUMRATING:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_ACCCUMRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALTRAVELTIME:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALTRAVELTIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALACCPEDALPRESSTIME:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALACCPEDALPRESSTIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_ACCPEDALPRESSRANGE1:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_ACCPEDALPRESSRANGE1;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_ACCPEDALPRESSRANGE1PER:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_ACCPEDALPRESSRANGE1PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_ACCPEDALPRESSRANGE2:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_ACCPEDALPRESSRANGE2;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_ACCPEDALPRESSRANGE2PER:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_ACCPEDALPRESSRANGE2PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_ACCPEDALPRESSRANGE3:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_ACCPEDALPRESSRANGE3;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_ACCPEDALPRESSRANGE3PER:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_ACCPEDALPRESSRANGE3PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_ACCPEDALPRESSRANGE4:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_ACCPEDALPRESSRANGE4;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_ACCPEDALPRESSRANGE4PER:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_ACCPEDALPRESSRANGE4PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_ACCPEDALPRESSNO:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_ACCPEDALPRESSNO;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_ACCPEDALPRESNOPER:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_ACCPEDALPRESNOPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_AVGACCPEDALPOS:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_AVGACCPEDALPOS;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_ACCHARSHCOUNT:                                        {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_ACCHARSHCOUNT;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_VEHICLE_TXMNVARIANT:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_VEHICLE_TXMNVARIANT;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_GSINSTRATING:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_GSINSTRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_GSCUMRATING:                                          {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_GSCUMRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALDISTVALIDGEAR_GEARSHIFT:                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALDISTVALIDGEAR_GEARSHIFT;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALTIMEVALIDGEAR_GEARSHIFT:                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALTIMEVALIDGEAR_GEARSHIFT;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TIMEGEAR1:                                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TIMEGEAR1;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_DISTGEAR1:                                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_DISTGEAR1;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TIMEGEAR1PER:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TIMEGEAR1PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_DISTGEAR1PER:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_DISTGEAR1PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TIMEGEAR2:                                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TIMEGEAR2;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_DISTGEAR2:                                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_DISTGEAR2;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TIMEGEAR2PER:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TIMEGEAR2PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_DISTGEAR2PER:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_DISTGEAR2PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TIMEGEAR3:                                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TIMEGEAR3;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_DISTGEAR3:                                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_DISTGEAR3;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TIMEGEAR3PER:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TIMEGEAR3PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_DISTGEAR3PER:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_DISTGEAR3PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TIMEGEAR4:                                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TIMEGEAR4;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_DISTGEAR4:                                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_DISTGEAR4;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TIMEGEAR4PER:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TIMEGEAR4PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_DISTGEAR4PER:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_DISTGEAR4PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TIMEGEAR5:                                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TIMEGEAR5;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_DISTGEAR5:                                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_DISTGEAR5;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TIMEGEAR5PER:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TIMEGEAR5PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_DISTGEAR5PER:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_DISTGEAR5PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TIMEGEAR6:                                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TIMEGEAR6;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_DISTGEAR6:                                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_DISTGEAR6;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TIMEGEAR6PER:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TIMEGEAR6PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_DISTGEAR6PER:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_DISTGEAR6PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_MOSTTIMEGEAR:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_MOSTTIMEGEAR;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALDISTVALIDGEAR:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALDISTVALIDGEAR;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALDISTWRONGGEAR:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALDISTWRONGGEAR;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALDISTDOWNINDI:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALDISTDOWNINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALDISTUPINDI:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALDISTUPINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_AVGDISTWRONGINDI:                                     {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_AVGDISTWRONGINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_AVGDISTDOWNINDI:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_AVGDISTDOWNINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_AVGDISTUPINDI:                                        {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_AVGDISTUPINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALDISTWRONGGEARPER:                                {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALDISTWRONGGEARPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALDISTDOWNINDIPER:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALDISTDOWNINDIPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALDISTUPINDIPER:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALDISTUPINDIPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALTIMEVALIDGEAR:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALTIMEVALIDGEAR;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALTIMEWRONGGEAR:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALTIMEWRONGGEAR;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALTIMEDOWNINDI:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALTIMEDOWNINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALTIMEUPINDI:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALTIMEUPINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALTIMEWRONGGEARPER:                                {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALTIMEWRONGGEARPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALTIMEDOWNINDIPER:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALTIMEDOWNINDIPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALTIMEUPINDIPER:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALTIMEUPINDIPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALCOUNTWRONGGEAR:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALCOUNTWRONGGEAR;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALCOUNTDOWNINDI:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALCOUNTDOWNINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALCOUNTUPINDI:                                     {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALCOUNTUPINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALCOUNTDOWNINDIPER:                                {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALCOUNTDOWNINDIPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALCOUNTUPINDIPER:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALCOUNTUPINDIPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_AVGCOUNTUPINDI:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_AVGCOUNTUPINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_AVGCOUNTDOWNINDI:                                     {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_AVGCOUNTDOWNINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALTIMECORRECTGEARPER:                              {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALTIMECORRECTGEARPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_AVGGEARSHIFT:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_AVGGEARSHIFT;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_NOOFGEARSHIFT:                                        {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_NOOFGEARSHIFT;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_ODODISTPERTRIP:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_ODODISTPERTRIP;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TOPSPEED:                                             {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOPSPEED;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_DRIVEINSTRATING:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_DRIVEINSTRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_DRIVECUMURATING:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_DRIVECUMURATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_SPEEDBAND1TIME:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_SPEEDBAND1TIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_SPEEDBAND1TIMEPER:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_SPEEDBAND1TIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_SPEEDBAND2TIME:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_SPEEDBAND2TIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_SPEEDBAND2TIMEPER:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_SPEEDBAND2TIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_SPEEDBAND3TIME:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_SPEEDBAND3TIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_SPEEDBAND3TIMEPER:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_SPEEDBAND3TIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_SPEEDBAND4TIME:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_SPEEDBAND4TIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_SPEEDBAND4TIMEPER:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_SPEEDBAND4TIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TRIPDIST:                                             {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TRIPDIST;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TRIPDURATION:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TRIPDURATION;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_AVGSPEED:                                             {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_AVGSPEED;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_AVGFUELECO:                                           {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_AVGFUELECO;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_OVERALLINSTRATING:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_OVERALLINSTRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_OVERALLCUMURATING:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_OVERALLCUMURATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_PERTIMEWITHOUTSEATBELT:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_PERTIMEWITHOUTSEATBELT;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_PERTIMEWITHSEATBELT:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_PERTIMEWITHSEATBELT;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_SEATBELTFACTOR:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_SEATBELTFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_NOOFTIMEWITHOUTSEATBELT:                              {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_NOOFTIMEWITHOUTSEATBELT;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_NOOFTIMEWITHSEATBELT:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_NOOFTIMEWITHSEATBELT;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_NOOFTIMEWITHOUTSEATBELTPER:                           {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_NOOFTIMEWITHOUTSEATBELTPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_DOORCLOSETIMEPER:                                     {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_DOORCLOSETIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_DOOROPENTIMEPER:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_DOOROPENTIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TIMEHIGHSPEEDCLTBRKPRESSEDPER:                        {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TIMEHIGHSPEEDCLTBRKPRESSEDPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TOTALTIMEHIGHSPEEDPER:                                {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TOTALTIMEHIGHSPEEDPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_SRSFACTOR:                                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_SRSFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TEABREAKFACTOR:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TEABREAKFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TRLFACTOR:                                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TRLFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TLLFACTOR:                                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TLLFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TBLFACTOR:                                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TBLFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TFLFACTOR:                                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TFLFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TPLFACTOR:                                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TPLFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_TRVLFACTOR:                                           {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TRVLFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_BRKFLDFACTOR:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_BRKFLDFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_OILPRFACTOR:                                          {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_OILPRFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_WIFFACTOR:                                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_WIFFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_VEHICLEHEALTH:                                        {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_VEHICLEHEALTH;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_SAFETYINSTRATING:                                     {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_SAFETYINSTRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPA_SAFETYCUMRATING:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_SAFETYCUMRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_FUELECOINSTRATING:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_FUELECOINSTRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_FUELECOCUMRATING:                                     {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_FUELECOCUMRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALTIME_ENGINEIDLE:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALTIME_ENGINEIDLE;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_IDLETIME:                                             {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_IDLETIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_IDLETIMEPER:                                          {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_IDLETIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALFUELIDLE:                                        {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALFUELIDLE;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALTIME_RPMEFFINFO:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALTIME_RPMEFFINFO;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALDIST:                                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALDIST;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_EFF_RPMTIMEAMBER:                                     {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_EFF_RPMTIMEAMBER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_EFF_RPMTIMEAMBERPER:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_EFF_RPMTIMEAMBERPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_EFF_RPMTIMEGREEN:                                     {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_EFF_RPMTIMEGREEN;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_EFF_RPMTIMEGREENPER:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_EFF_RPMTIMEGREENPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_EFF_RPMTIMERED:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_EFF_RPMTIMERED;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_EFF_RPMTIMEREDPER:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_EFF_RPMTIMEREDPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_EFF_RPMDISTAMBER:                                     {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_EFF_RPMDISTAMBER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_EFF_RPMDISTAMBERPER:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_EFF_RPMDISTAMBERPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_EFF_RPMDISTGREEN:                                     {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_EFF_RPMDISTGREEN;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_EFF_RPMDISTGREENPER:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_EFF_RPMDISTGREENPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_EFF_RPMDISTRED:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_EFF_RPMDISTRED;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_EFF_RPMDISTREDPER:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_EFF_RPMDISTREDPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_AVGENG_RPM:                                           {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_AVGENG_RPM;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALTIME_ACON:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALTIME_ACON;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_AC_ONTIME:                                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_AC_ONTIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_AC_ONTIMEPER:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_AC_ONTIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALTIME_CLT_ACC:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALTIME_CLT_ACC;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_CLT_ACCTIME:                                          {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_CLT_ACCTIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_CLT_ACCTIMEPER:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_CLT_ACCTIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_BRKINSTRATING:                                        {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_BRKINSTRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_ACCLN:                                                {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_ACCLN;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_NOOFBRKCYCLE:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_NOOFBRKCYCLE;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_BRKCUMRATING:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_BRKCUMRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALBRK:                                             {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALBRK;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_NORMALBRK:                                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_NORMALBRK;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_NORMALBRKPER:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_NORMALBRKPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_MODERATEBRK:                                          {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_MODERATEBRK;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_MODERATEBRKPER:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_MODERATEBRKPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_HEAVYBRK:                                             {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_HEAVYBRK;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_HEAVYBRKPER:                                          {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_HEAVYBRKPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_PANICBRK:                                             {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_PANICBRK;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_PANICBRKPER:                                          {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_PANICBRKPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_HARSHBRK:                                             {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_HARSHBRK;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_HARSHBRKPER:                                          {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_HARSHBRKPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_AVGBRKCOUNT:                                          {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_AVGBRKCOUNT;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_ODODISTPERTRIP_BRAKING:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_ODODISTPERTRIP_BRAKING;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_ACCINSTRATING:                                        {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_ACCINSTRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_ACCCUMRATING:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_ACCCUMRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALTRAVELTIME:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALTRAVELTIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALACCPEDALPRESSTIME:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALACCPEDALPRESSTIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_ACCPEDALPRESSRANGE1:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_ACCPEDALPRESSRANGE1;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_ACCPEDALPRESSRANGE1PER:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_ACCPEDALPRESSRANGE1PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_ACCPEDALPRESSRANGE2:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_ACCPEDALPRESSRANGE2;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_ACCPEDALPRESSRANGE2PER:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_ACCPEDALPRESSRANGE2PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_ACCPEDALPRESSRANGE3:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_ACCPEDALPRESSRANGE3;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_ACCPEDALPRESSRANGE3PER:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_ACCPEDALPRESSRANGE3PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_ACCPEDALPRESSRANGE4:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_ACCPEDALPRESSRANGE4;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_ACCPEDALPRESSRANGE4PER:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_ACCPEDALPRESSRANGE4PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_ACCPEDALPRESSNO:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_ACCPEDALPRESSNO;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_ACCPEDALPRESNOPER:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_ACCPEDALPRESNOPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_AVGACCPEDALPOS:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_AVGACCPEDALPOS;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_ACCHARSHCOUNT:                                        {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_ACCHARSHCOUNT;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_VEHICLE_TXMNVARIANT:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_VEHICLE_TXMNVARIANT;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_GSINSTRATING:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_GSINSTRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_GSCUMRATING:                                          {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_GSCUMRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALDISTVALIDGEAR_GEARSHIFT:                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALDISTVALIDGEAR_GEARSHIFT;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALTIMEVALIDGEAR_GEARSHIFT:                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALTIMEVALIDGEAR_GEARSHIFT;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TIMEGEAR1:                                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TIMEGEAR1;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_DISTGEAR1:                                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_DISTGEAR1;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TIMEGEAR1PER:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TIMEGEAR1PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_DISTGEAR1PER:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_DISTGEAR1PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TIMEGEAR2:                                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TIMEGEAR2;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_DISTGEAR2:                                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_DISTGEAR2;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TIMEGEAR2PER:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TIMEGEAR2PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_DISTGEAR2PER:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_DISTGEAR2PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TIMEGEAR3:                                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TIMEGEAR3;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_DISTGEAR3:                                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_DISTGEAR3;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TIMEGEAR3PER:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TIMEGEAR3PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_DISTGEAR3PER:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_DISTGEAR3PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TIMEGEAR4:                                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TIMEGEAR4;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_DISTGEAR4:                                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_DISTGEAR4;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TIMEGEAR4PER:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TIMEGEAR4PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_DISTGEAR4PER:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_DISTGEAR4PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TIMEGEAR5:                                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TIMEGEAR5;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_DISTGEAR5:                                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_DISTGEAR5;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TIMEGEAR5PER:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TIMEGEAR5PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_DISTGEAR5PER:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_DISTGEAR5PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TIMEGEAR6:                                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TIMEGEAR6;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_DISTGEAR6:                                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_DISTGEAR6;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TIMEGEAR6PER:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TIMEGEAR6PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_DISTGEAR6PER:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_DISTGEAR6PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_MOSTTIMEGEAR:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_MOSTTIMEGEAR;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALDISTVALIDGEAR:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALDISTVALIDGEAR;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALDISTWRONGGEAR:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALDISTWRONGGEAR;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALDISTDOWNINDI:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALDISTDOWNINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALDISTUPINDI:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALDISTUPINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_AVGDISTWRONGINDI:                                     {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_AVGDISTWRONGINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_AVGDISTDOWNINDI:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_AVGDISTDOWNINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_AVGDISTUPINDI:                                        {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_AVGDISTUPINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALDISTWRONGGEARPER:                                {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALDISTWRONGGEARPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALDISTDOWNINDIPER:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALDISTDOWNINDIPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALDISTUPINDIPER:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALDISTUPINDIPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALTIMEVALIDGEAR:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALTIMEVALIDGEAR;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALTIMEWRONGGEAR:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALTIMEWRONGGEAR;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALTIMEDOWNINDI:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALTIMEDOWNINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALTIMEUPINDI:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALTIMEUPINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALTIMEWRONGGEARPER:                                {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALTIMEWRONGGEARPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALTIMEDOWNINDIPER:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALTIMEDOWNINDIPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALTIMEUPINDIPER:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALTIMEUPINDIPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALCOUNTWRONGGEAR:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALCOUNTWRONGGEAR;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALCOUNTDOWNINDI:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALCOUNTDOWNINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALCOUNTUPINDI:                                     {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALCOUNTUPINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALCOUNTDOWNINDIPER:                                {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALCOUNTDOWNINDIPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALCOUNTUPINDIPER:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALCOUNTUPINDIPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_AVGCOUNTUPINDI:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_AVGCOUNTUPINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_AVGCOUNTDOWNINDI:                                     {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_AVGCOUNTDOWNINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALTIMECORRECTGEARPER:                              {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALTIMECORRECTGEARPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_AVGGEARSHIFT:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_AVGGEARSHIFT;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_NOOFGEARSHIFT:                                        {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_NOOFGEARSHIFT;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_ODODISTPERTRIP:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_ODODISTPERTRIP;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TOPSPEED:                                             {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOPSPEED;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_DRIVEINSTRATING:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_DRIVEINSTRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_DRIVECUMURATING:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_DRIVECUMURATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_SPEEDBAND1TIME:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_SPEEDBAND1TIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_SPEEDBAND1TIMEPER:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_SPEEDBAND1TIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_SPEEDBAND2TIME:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_SPEEDBAND2TIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_SPEEDBAND2TIMEPER:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_SPEEDBAND2TIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_SPEEDBAND3TIME:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_SPEEDBAND3TIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_SPEEDBAND3TIMEPER:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_SPEEDBAND3TIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_SPEEDBAND4TIME:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_SPEEDBAND4TIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_SPEEDBAND4TIMEPER:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_SPEEDBAND4TIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TRIPDIST:                                             {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TRIPDIST;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TRIPDURATION:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TRIPDURATION;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_AVGSPEED:                                             {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_AVGSPEED;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_AVGFUELECO:                                           {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_AVGFUELECO;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_OVERALLINSTRATING:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_OVERALLINSTRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_OVERALLCUMURATING:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_OVERALLCUMURATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_PERTIMEWITHOUTSEATBELT:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_PERTIMEWITHOUTSEATBELT;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_PERTIMEWITHSEATBELT:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_PERTIMEWITHSEATBELT;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_SEATBELTFACTOR:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_SEATBELTFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_NOOFTIMEWITHOUTSEATBELT:                              {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_NOOFTIMEWITHOUTSEATBELT;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_NOOFTIMEWITHSEATBELT:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_NOOFTIMEWITHSEATBELT;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_NOOFTIMEWITHOUTSEATBELTPER:                           {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_NOOFTIMEWITHOUTSEATBELTPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_DOORCLOSETIMEPER:                                     {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_DOORCLOSETIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_DOOROPENTIMEPER:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_DOOROPENTIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TIMEHIGHSPEEDCLTBRKPRESSEDPER:                        {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TIMEHIGHSPEEDCLTBRKPRESSEDPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TOTALTIMEHIGHSPEEDPER:                                {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TOTALTIMEHIGHSPEEDPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_SRSFACTOR:                                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_SRSFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TEABREAKFACTOR:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TEABREAKFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TRLFACTOR:                                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TRLFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TLLFACTOR:                                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TLLFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TBLFACTOR:                                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TBLFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TFLFACTOR:                                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TFLFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TPLFACTOR:                                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TPLFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_TRVLFACTOR:                                           {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TRVLFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_BRKFLDFACTOR:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_BRKFLDFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_OILPRFACTOR:                                          {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_OILPRFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_WIFFACTOR:                                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_WIFFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_VEHICLEHEALTH:                                        {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_VEHICLEHEALTH;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_SAFETYINSTRATING:                                     {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_SAFETYINSTRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::TRIPB_SAFETYCUMRATING:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_SAFETYCUMRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_FUELECOINSTRATING:                              {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_FUELECOINSTRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_FUELECOCUMRATING:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_FUELECOCUMRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALTIME_ENGINEIDLE:                           {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALTIME_ENGINEIDLE;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_IDLETIME:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_IDLETIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_IDLETIMEPER:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_IDLETIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALFUELIDLE:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALFUELIDLE;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALTIME_RPMEFFINFO:                           {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALTIME_RPMEFFINFO;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALDIST:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALDIST;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_EFF_RPMTIMEAMBER:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_EFF_RPMTIMEAMBER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_EFF_RPMTIMEAMBERPER:                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_EFF_RPMTIMEAMBERPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_EFF_RPMTIMEGREEN:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_EFF_RPMTIMEGREEN;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_EFF_RPMTIMEGREENPER:                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_EFF_RPMTIMEGREENPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_EFF_RPMTIMERED:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_EFF_RPMTIMERED;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_EFF_RPMTIMEREDPER:                              {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_EFF_RPMTIMEREDPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_EFF_RPMDISTAMBER:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_EFF_RPMDISTAMBER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_EFF_RPMDISTAMBERPER:                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_EFF_RPMDISTAMBERPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_EFF_RPMDISTGREEN:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_EFF_RPMDISTGREEN;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_EFF_RPMDISTGREENPER:                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_EFF_RPMDISTGREENPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_EFF_RPMDISTRED:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_EFF_RPMDISTRED;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_EFF_RPMDISTREDPER:                              {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_EFF_RPMDISTREDPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_AVGENG_RPM:                                     {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_AVGENG_RPM;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALTIME_ACON:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALTIME_ACON;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_AC_ONTIME:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_AC_ONTIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_AC_ONTIMEPER:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_AC_ONTIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALTIME_CLT_ACC:                              {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALTIME_CLT_ACC;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_CLT_ACCTIME:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_CLT_ACCTIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_CLT_ACCTIMEPER:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_CLT_ACCTIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_BRKINSTRATING:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_BRKINSTRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_ACCLN:                                          {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_ACCLN;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_NOOFBRKCYCLE:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_NOOFBRKCYCLE;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_BRKCUMRATING:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_BRKCUMRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALBRK:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALBRK;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_NORMALBRK:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_NORMALBRK;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_NORMALBRKPER:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_NORMALBRKPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_MODERATEBRK:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_MODERATEBRK;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_MODERATEBRKPER:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_MODERATEBRKPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_HEAVYBRK:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_HEAVYBRK;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_HEAVYBRKPER:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_HEAVYBRKPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_PANICBRK:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_PANICBRK;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_PANICBRKPER:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_PANICBRKPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_HARSHBRK:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_HARSHBRK;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_HARSHBRKPER:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_HARSHBRKPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_AVGBRKCOUNT:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_AVGBRKCOUNT;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_ODODISTPERTRIP_BRAKING:                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_ODODISTPERTRIP_BRAKING;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_ACCINSTRATING:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_ACCINSTRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_ACCCUMRATING:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_ACCCUMRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALTRAVELTIME:                                {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALTRAVELTIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALACCPEDALPRESSTIME:                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALACCPEDALPRESSTIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_ACCPEDALPRESSRANGE1:                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_ACCPEDALPRESSRANGE1;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_ACCPEDALPRESSRANGE1PER:                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_ACCPEDALPRESSRANGE1PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_ACCPEDALPRESSRANGE2:                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_ACCPEDALPRESSRANGE2;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_ACCPEDALPRESSRANGE2PER:                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_ACCPEDALPRESSRANGE2PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_ACCPEDALPRESSRANGE3:                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_ACCPEDALPRESSRANGE3;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_ACCPEDALPRESSRANGE3PER:                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_ACCPEDALPRESSRANGE3PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_ACCPEDALPRESSRANGE4:                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_ACCPEDALPRESSRANGE4;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_ACCPEDALPRESSRANGE4PER:                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_ACCPEDALPRESSRANGE4PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_ACCPEDALPRESSNO:                                {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_ACCPEDALPRESSNO;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_ACCPEDALPRESNOPER:                              {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_ACCPEDALPRESNOPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_AVGACCPEDALPOS:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_AVGACCPEDALPOS;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_ACCHARSHCOUNT:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_ACCHARSHCOUNT;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_VEHICLE_TXMNVARIANT:                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_VEHICLE_TXMNVARIANT;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_GSINSTRATING:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_GSINSTRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_GSCUMRATING:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_GSCUMRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALDISTVALIDGEAR_GEARSHIFT:                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALDISTVALIDGEAR_GEARSHIFT;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALTIMEVALIDGEAR_GEARSHIFT:                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALTIMEVALIDGEAR_GEARSHIFT;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TIMEGEAR1:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TIMEGEAR1;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_DISTGEAR1:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_DISTGEAR1;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TIMEGEAR1PER:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TIMEGEAR1PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_DISTGEAR1PER:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_DISTGEAR1PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TIMEGEAR2:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TIMEGEAR2;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_DISTGEAR2:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_DISTGEAR2;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TIMEGEAR2PER:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TIMEGEAR2PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_DISTGEAR2PER:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_DISTGEAR2PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TIMEGEAR3:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TIMEGEAR3;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_DISTGEAR3:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_DISTGEAR3;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TIMEGEAR3PER:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TIMEGEAR3PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_DISTGEAR3PER:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_DISTGEAR3PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TIMEGEAR4:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TIMEGEAR4;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_DISTGEAR4:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_DISTGEAR4;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TIMEGEAR4PER:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TIMEGEAR4PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_DISTGEAR4PER:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_DISTGEAR4PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TIMEGEAR5:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TIMEGEAR5;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_DISTGEAR5:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_DISTGEAR5;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TIMEGEAR5PER:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TIMEGEAR5PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_DISTGEAR5PER:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_DISTGEAR5PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TIMEGEAR6:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TIMEGEAR6;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_DISTGEAR6:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_DISTGEAR6;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TIMEGEAR6PER:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TIMEGEAR6PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_DISTGEAR6PER:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_DISTGEAR6PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_MOSTTIMEGEAR:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_MOSTTIMEGEAR;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALDISTVALIDGEAR:                             {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALDISTVALIDGEAR;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALDISTWRONGGEAR:                             {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALDISTWRONGGEAR;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALDISTDOWNINDI:                              {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALDISTDOWNINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALDISTUPINDI:                                {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALDISTUPINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_AVGDISTWRONGINDI:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_AVGDISTWRONGINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_AVGDISTDOWNINDI:                                {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_AVGDISTDOWNINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_AVGDISTUPINDI:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_AVGDISTUPINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALDISTWRONGGEARPER:                          {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALDISTWRONGGEARPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALDISTDOWNINDIPER:                           {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALDISTDOWNINDIPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALDISTUPINDIPER:                             {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALDISTUPINDIPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALTIMEVALIDGEAR:                             {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALTIMEVALIDGEAR;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALTIMEWRONGGEAR:                             {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALTIMEWRONGGEAR;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALTIMEDOWNINDI:                              {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALTIMEDOWNINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALTIMEUPINDI:                                {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALTIMEUPINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALTIMEWRONGGEARPER:                          {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALTIMEWRONGGEARPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALTIMEDOWNINDIPER:                           {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALTIMEDOWNINDIPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALTIMEUPINDIPER:                             {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALTIMEUPINDIPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALCOUNTWRONGGEAR:                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALCOUNTWRONGGEAR;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALCOUNTDOWNINDI:                             {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALCOUNTDOWNINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALCOUNTUPINDI:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALCOUNTUPINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALCOUNTDOWNINDIPER:                          {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALCOUNTDOWNINDIPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALCOUNTUPINDIPER:                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALCOUNTUPINDIPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_AVGCOUNTUPINDI:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_AVGCOUNTUPINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_AVGCOUNTDOWNINDI:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_AVGCOUNTDOWNINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALTIMECORRECTGEARPER:                        {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALTIMECORRECTGEARPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_AVGGEARSHIFT:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_AVGGEARSHIFT;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_NOOFGEARSHIFT:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_NOOFGEARSHIFT;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_ODODISTPERTRIP:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_ODODISTPERTRIP;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOPSPEED:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOPSPEED;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_DRIVEINSTRATING:                                {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_DRIVEINSTRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_DRIVECUMURATING:                                {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_DRIVECUMURATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_SPEEDBAND1TIME:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_SPEEDBAND1TIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_SPEEDBAND1TIMEPER:                              {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_SPEEDBAND1TIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_SPEEDBAND2TIME:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_SPEEDBAND2TIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_SPEEDBAND2TIMEPER:                              {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_SPEEDBAND2TIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_SPEEDBAND3TIME:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_SPEEDBAND3TIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_SPEEDBAND3TIMEPER:                              {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_SPEEDBAND3TIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_SPEEDBAND4TIME:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_SPEEDBAND4TIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_SPEEDBAND4TIMEPER:                              {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_SPEEDBAND4TIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TRIPDIST:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TRIPDIST;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TRIPDURATION:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TRIPDURATION;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_AVGSPEED:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_AVGSPEED;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_AVGFUELECO:                                     {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_AVGFUELECO;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_OVERALLINSTRATING:                              {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_OVERALLINSTRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_OVERALLCUMURATING:                              {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_OVERALLCUMURATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_PERTIMEWITHOUTSEATBELT:                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_PERTIMEWITHOUTSEATBELT;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_PERTIMEWITHSEATBELT:                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_PERTIMEWITHSEATBELT;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_SEATBELTFACTOR:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_SEATBELTFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_NOOFTIMEWITHOUTSEATBELT:                        {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_NOOFTIMEWITHOUTSEATBELT;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_NOOFTIMEWITHSEATBELT:                           {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_NOOFTIMEWITHSEATBELT;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_NOOFTIMEWITHOUTSEATBELTPER:                     {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_NOOFTIMEWITHOUTSEATBELTPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_DOORCLOSETIMEPER:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_DOORCLOSETIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_DOOROPENTIMEPER:                                {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_DOOROPENTIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TIMEHIGHSPEEDCLTBRKPRESSEDPER:                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TIMEHIGHSPEEDCLTBRKPRESSEDPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TOTALTIMEHIGHSPEEDPER:                          {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TOTALTIMEHIGHSPEEDPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_SRSFACTOR:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_SRSFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TEABREAKFACTOR:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TEABREAKFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TRLFACTOR:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TRLFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TLLFACTOR:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TLLFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TBLFACTOR:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TBLFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TFLFACTOR:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TFLFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TPLFACTOR:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TPLFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_TRVLFACTOR:                                     {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TRVLFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_BRKFLDFACTOR:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_BRKFLDFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_OILPRFACTOR:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_OILPRFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_WIFFACTOR:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_WIFFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_VEHICLEHEALTH:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_VEHICLEHEALTH;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_SAFETYINSTRATING:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_SAFETYINSTRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::OVERALLTRIP_SAFETYCUMRATING:                                {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_SAFETYCUMRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_FUELECOINSTRATING:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_FUELECOINSTRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_FUELECOCUMRATING:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_FUELECOCUMRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALTIME_ENGINEIDLE:                              {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALTIME_ENGINEIDLE;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_IDLETIME:                                          {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_IDLETIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_IDLETIMEPER:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_IDLETIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALFUELIDLE:                                     {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALFUELIDLE;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALTIME_RPMEFFINFO:                              {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALTIME_RPMEFFINFO;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALDIST:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALDIST;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_EFF_RPMTIMEAMBER:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_EFF_RPMTIMEAMBER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_EFF_RPMTIMEAMBERPER:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_EFF_RPMTIMEAMBERPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_EFF_RPMTIMEGREEN:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_EFF_RPMTIMEGREEN;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_EFF_RPMTIMEGREENPER:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_EFF_RPMTIMEGREENPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_EFF_RPMTIMERED:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_EFF_RPMTIMERED;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_EFF_RPMTIMEREDPER:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_EFF_RPMTIMEREDPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_EFF_RPMDISTAMBER:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_EFF_RPMDISTAMBER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_EFF_RPMDISTAMBERPER:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_EFF_RPMDISTAMBERPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_EFF_RPMDISTGREEN:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_EFF_RPMDISTGREEN;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_EFF_RPMDISTGREENPER:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_EFF_RPMDISTGREENPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_EFF_RPMDISTRED:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_EFF_RPMDISTRED;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_EFF_RPMDISTREDPER:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_EFF_RPMDISTREDPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_AVGENG_RPM:                                        {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_AVGENG_RPM;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALTIME_ACON:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALTIME_ACON;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_AC_ONTIME:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_AC_ONTIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_AC_ONTIMEPER:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_AC_ONTIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALTIME_CLT_ACC:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALTIME_CLT_ACC;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_CLT_ACCTIME:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_CLT_ACCTIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_CLT_ACCTIMEPER:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_CLT_ACCTIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_BRKINSTRATING:                                     {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_BRKINSTRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_ACCLN:                                             {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_ACCLN;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_NOOFBRKCYCLE:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_NOOFBRKCYCLE;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_BRKCUMRATING:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_BRKCUMRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALBRK:                                          {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALBRK;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_NORMALBRK:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_NORMALBRK;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_NORMALBRKPER:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_NORMALBRKPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_MODERATEBRK:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_MODERATEBRK;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_MODERATEBRKPER:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_MODERATEBRKPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_HEAVYBRK:                                          {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_HEAVYBRK;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_HEAVYBRKPER:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_HEAVYBRKPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_PANICBRK:                                          {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_PANICBRK;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_PANICBRKPER:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_PANICBRKPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_HARSHBRK:                                          {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_HARSHBRK;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_HARSHBRKPER:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_HARSHBRKPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_AVGBRKCOUNT:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_AVGBRKCOUNT;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_ODODISTPERTRIP_BRAKING:                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_ODODISTPERTRIP_BRAKING;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_ACCINSTRATING:                                     {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_ACCINSTRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_ACCCUMRATING:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_ACCCUMRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALTRAVELTIME:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALTRAVELTIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALACCPEDALPRESSTIME:                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALACCPEDALPRESSTIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_ACCPEDALPRESSRANGE1:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_ACCPEDALPRESSRANGE1;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_ACCPEDALPRESSRANGE1PER:                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_ACCPEDALPRESSRANGE1PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_ACCPEDALPRESSRANGE2:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_ACCPEDALPRESSRANGE2;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_ACCPEDALPRESSRANGE2PER:                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_ACCPEDALPRESSRANGE2PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_ACCPEDALPRESSRANGE3:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_ACCPEDALPRESSRANGE3;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_ACCPEDALPRESSRANGE3PER:                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_ACCPEDALPRESSRANGE3PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_ACCPEDALPRESSRANGE4:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_ACCPEDALPRESSRANGE4;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_ACCPEDALPRESSRANGE4PER:                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_ACCPEDALPRESSRANGE4PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_ACCPEDALPRESSNO:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_ACCPEDALPRESSNO;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_ACCPEDALPRESNOPER:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_ACCPEDALPRESNOPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_AVGACCPEDALPOS:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_AVGACCPEDALPOS;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_ACCHARSHCOUNT:                                     {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_ACCHARSHCOUNT;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_VEHICLE_TXMNVARIANT:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_VEHICLE_TXMNVARIANT;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_GSINSTRATING:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_GSINSTRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_GSCUMRATING:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_GSCUMRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALDISTVALIDGEAR_GEARSHIFT:                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALDISTVALIDGEAR_GEARSHIFT;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALTIMEVALIDGEAR_GEARSHIFT:                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALTIMEVALIDGEAR_GEARSHIFT;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TIMEGEAR1:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TIMEGEAR1;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_DISTGEAR1:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_DISTGEAR1;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TIMEGEAR1PER:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TIMEGEAR1PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_DISTGEAR1PER:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_DISTGEAR1PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TIMEGEAR2:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TIMEGEAR2;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_DISTGEAR2:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_DISTGEAR2;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TIMEGEAR2PER:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TIMEGEAR2PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_DISTGEAR2PER:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_DISTGEAR2PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TIMEGEAR3:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TIMEGEAR3;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_DISTGEAR3:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_DISTGEAR3;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TIMEGEAR3PER:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TIMEGEAR3PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_DISTGEAR3PER:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_DISTGEAR3PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TIMEGEAR4:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TIMEGEAR4;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_DISTGEAR4:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_DISTGEAR4;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TIMEGEAR4PER:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TIMEGEAR4PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_DISTGEAR4PER:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_DISTGEAR4PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TIMEGEAR5:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TIMEGEAR5;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_DISTGEAR5:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_DISTGEAR5;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TIMEGEAR5PER:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TIMEGEAR5PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_DISTGEAR5PER:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_DISTGEAR5PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TIMEGEAR6:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TIMEGEAR6;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_DISTGEAR6:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_DISTGEAR6;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TIMEGEAR6PER:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TIMEGEAR6PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_DISTGEAR6PER:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_DISTGEAR6PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_MOSTTIMEGEAR:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_MOSTTIMEGEAR;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALDISTVALIDGEAR:                                {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALDISTVALIDGEAR;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALDISTWRONGGEAR:                                {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALDISTWRONGGEAR;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALDISTDOWNINDI:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALDISTDOWNINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALDISTUPINDI:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALDISTUPINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_AVGDISTWRONGINDI:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_AVGDISTWRONGINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_AVGDISTDOWNINDI:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_AVGDISTDOWNINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_AVGDISTUPINDI:                                     {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_AVGDISTUPINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALDISTWRONGGEARPER:                             {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALDISTWRONGGEARPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALDISTDOWNINDIPER:                              {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALDISTDOWNINDIPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALDISTUPINDIPER:                                {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALDISTUPINDIPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALTIMEVALIDGEAR:                                {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALTIMEVALIDGEAR;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALTIMEWRONGGEAR:                                {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALTIMEWRONGGEAR;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALTIMEDOWNINDI:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALTIMEDOWNINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALTIMEUPINDI:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALTIMEUPINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALTIMEWRONGGEARPER:                             {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALTIMEWRONGGEARPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALTIMEDOWNINDIPER:                              {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALTIMEDOWNINDIPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALTIMEUPINDIPER:                                {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALTIMEUPINDIPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALCOUNTWRONGGEAR:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALCOUNTWRONGGEAR;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALCOUNTDOWNINDI:                                {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALCOUNTDOWNINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALCOUNTUPINDI:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALCOUNTUPINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALCOUNTDOWNINDIPER:                             {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALCOUNTDOWNINDIPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALCOUNTUPINDIPER:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALCOUNTUPINDIPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_AVGCOUNTUPINDI:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_AVGCOUNTUPINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_AVGCOUNTDOWNINDI:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_AVGCOUNTDOWNINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALTIMECORRECTGEARPER:                           {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALTIMECORRECTGEARPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_AVGGEARSHIFT:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_AVGGEARSHIFT;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_NOOFGEARSHIFT:                                     {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_NOOFGEARSHIFT;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_ODODISTPERTRIP:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_ODODISTPERTRIP;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOPSPEED:                                          {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOPSPEED;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_DRIVEINSTRATING:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_DRIVEINSTRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_DRIVECUMURATING:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_DRIVECUMURATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_SPEEDBAND1TIME:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_SPEEDBAND1TIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_SPEEDBAND1TIMEPER:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_SPEEDBAND1TIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_SPEEDBAND2TIME:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_SPEEDBAND2TIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_SPEEDBAND2TIMEPER:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_SPEEDBAND2TIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_SPEEDBAND3TIME:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_SPEEDBAND3TIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_SPEEDBAND3TIMEPER:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_SPEEDBAND3TIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_SPEEDBAND4TIME:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_SPEEDBAND4TIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_SPEEDBAND4TIMEPER:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_SPEEDBAND4TIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TRIPDIST:                                          {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TRIPDIST;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TRIPDURATION:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TRIPDURATION;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_AVGSPEED:                                          {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_AVGSPEED;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_AVGFUELECO:                                        {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_AVGFUELECO;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_OVERALLINSTRATING:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_OVERALLINSTRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_OVERALLCUMURATING:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_OVERALLCUMURATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_PERTIMEWITHOUTSEATBELT:                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_PERTIMEWITHOUTSEATBELT;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_PERTIMEWITHSEATBELT:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_PERTIMEWITHSEATBELT;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_SEATBELTFACTOR:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_SEATBELTFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_NOOFTIMEWITHOUTSEATBELT:                           {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_NOOFTIMEWITHOUTSEATBELT;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_NOOFTIMEWITHSEATBELT:                              {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_NOOFTIMEWITHSEATBELT;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_NOOFTIMEWITHOUTSEATBELTPER:                        {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_NOOFTIMEWITHOUTSEATBELTPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_DOORCLOSETIMEPER:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_DOORCLOSETIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_DOOROPENTIMEPER:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_DOOROPENTIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TIMEHIGHSPEEDCLTBRKPRESSEDPER:                     {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TIMEHIGHSPEEDCLTBRKPRESSEDPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TOTALTIMEHIGHSPEEDPER:                             {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TOTALTIMEHIGHSPEEDPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_SRSFACTOR:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_SRSFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TEABREAKFACTOR:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TEABREAKFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TRLFACTOR:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TRLFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TLLFACTOR:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TLLFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TBLFACTOR:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TBLFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TFLFACTOR:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TFLFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TPLFACTOR:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TPLFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_TRVLFACTOR:                                        {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_TRVLFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_BRKFLDFACTOR:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_BRKFLDFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_OILPRFACTOR:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_OILPRFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_WIFFACTOR:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_WIFFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_VEHICLEHEALTH:                                     {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_VEHICLEHEALTH;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_SAFETYINSTRATING:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_SAFETYINSTRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::BESTTRIP_SAFETYCUMRATING:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_BESTTRIP_SAFETYCUMRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_FUELECOINSTRATING:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_FUELECOINSTRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_FUELECOCUMRATING:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_FUELECOCUMRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALTIME_ENGINEIDLE:                              {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALTIME_ENGINEIDLE;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_IDLETIME:                                          {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_IDLETIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_IDLETIMEPER:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_IDLETIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALFUELIDLE:                                     {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALFUELIDLE;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALTIME_RPMEFFINFO:                              {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALTIME_RPMEFFINFO;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALDIST:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALDIST;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_EFF_RPMTIMEAMBER:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_EFF_RPMTIMEAMBER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_EFF_RPMTIMEAMBERPER:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_EFF_RPMTIMEAMBERPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_EFF_RPMTIMEGREEN:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_EFF_RPMTIMEGREEN;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_EFF_RPMTIMEGREENPER:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_EFF_RPMTIMEGREENPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_EFF_RPMTIMERED:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_EFF_RPMTIMERED;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_EFF_RPMTIMEREDPER:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_EFF_RPMTIMEREDPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_EFF_RPMDISTAMBER:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_EFF_RPMDISTAMBER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_EFF_RPMDISTAMBERPER:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_EFF_RPMDISTAMBERPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_EFF_RPMDISTGREEN:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_EFF_RPMDISTGREEN;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_EFF_RPMDISTGREENPER:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_EFF_RPMDISTGREENPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_EFF_RPMDISTRED:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_EFF_RPMDISTRED;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_EFF_RPMDISTREDPER:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_EFF_RPMDISTREDPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_AVGENG_RPM:                                        {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_AVGENG_RPM;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALTIME_ACON:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALTIME_ACON;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_AC_ONTIME:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_AC_ONTIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_AC_ONTIMEPER:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_AC_ONTIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALTIME_CLT_ACC:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALTIME_CLT_ACC;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_CLT_ACCTIME:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_CLT_ACCTIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_CLT_ACCTIMEPER:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_CLT_ACCTIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_BRKINSTRATING:                                     {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_BRKINSTRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_ACCLN:                                             {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_ACCLN;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_NOOFBRKCYCLE:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_NOOFBRKCYCLE;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_BRKCUMRATING:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_BRKCUMRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALBRK:                                          {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALBRK;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_NORMALBRK:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_NORMALBRK;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_NORMALBRKPER:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_NORMALBRKPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_MODERATEBRK:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_MODERATEBRK;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_MODERATEBRKPER:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_MODERATEBRKPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_HEAVYBRK:                                          {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_HEAVYBRK;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_HEAVYBRKPER:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_HEAVYBRKPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_PANICBRK:                                          {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_PANICBRK;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_PANICBRKPER:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_PANICBRKPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_HARSHBRK:                                          {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_HARSHBRK;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_HARSHBRKPER:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_HARSHBRKPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_AVGBRKCOUNT:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_AVGBRKCOUNT;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_ODODISTPERTRIP_BRAKING:                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_ODODISTPERTRIP_BRAKING;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_ACCINSTRATING:                                     {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_ACCINSTRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_ACCCUMRATING:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_ACCCUMRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALTRAVELTIME:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALTRAVELTIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALACCPEDALPRESSTIME:                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALACCPEDALPRESSTIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_ACCPEDALPRESSRANGE1:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_ACCPEDALPRESSRANGE1;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_ACCPEDALPRESSRANGE1PER:                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_ACCPEDALPRESSRANGE1PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_ACCPEDALPRESSRANGE2:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_ACCPEDALPRESSRANGE2;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_ACCPEDALPRESSRANGE2PER:                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_ACCPEDALPRESSRANGE2PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_ACCPEDALPRESSRANGE3:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_ACCPEDALPRESSRANGE3;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_ACCPEDALPRESSRANGE3PER:                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_ACCPEDALPRESSRANGE3PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_ACCPEDALPRESSRANGE4:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_ACCPEDALPRESSRANGE4;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_ACCPEDALPRESSRANGE4PER:                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_ACCPEDALPRESSRANGE4PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_ACCPEDALPRESSNO:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_ACCPEDALPRESSNO;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_ACCPEDALPRESNOPER:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_ACCPEDALPRESNOPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_AVGACCPEDALPOS:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_AVGACCPEDALPOS;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_ACCHARSHCOUNT:                                     {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_ACCHARSHCOUNT;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_VEHICLE_TXMNVARIANT:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_VEHICLE_TXMNVARIANT;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_GSINSTRATING:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_GSINSTRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_GSCUMRATING:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_GSCUMRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALDISTVALIDGEAR_GEARSHIFT:                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALDISTVALIDGEAR_GEARSHIFT;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALTIMEVALIDGEAR_GEARSHIFT:                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALTIMEVALIDGEAR_GEARSHIFT;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TIMEGEAR1:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TIMEGEAR1;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_DISTGEAR1:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_DISTGEAR1;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TIMEGEAR1PER:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TIMEGEAR1PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_DISTGEAR1PER:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_DISTGEAR1PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TIMEGEAR2:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TIMEGEAR2;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_DISTGEAR2:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_DISTGEAR2;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TIMEGEAR2PER:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TIMEGEAR2PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_DISTGEAR2PER:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_DISTGEAR2PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TIMEGEAR3:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TIMEGEAR3;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_DISTGEAR3:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_DISTGEAR3;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TIMEGEAR3PER:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TIMEGEAR3PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_DISTGEAR3PER:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_DISTGEAR3PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TIMEGEAR4:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TIMEGEAR4;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_DISTGEAR4:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_DISTGEAR4;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TIMEGEAR4PER:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TIMEGEAR4PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_DISTGEAR4PER:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_DISTGEAR4PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TIMEGEAR5:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TIMEGEAR5;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_DISTGEAR5:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_DISTGEAR5;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TIMEGEAR5PER:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TIMEGEAR5PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_DISTGEAR5PER:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_DISTGEAR5PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TIMEGEAR6:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TIMEGEAR6;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_DISTGEAR6:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_DISTGEAR6;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TIMEGEAR6PER:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TIMEGEAR6PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_DISTGEAR6PER:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_DISTGEAR6PER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_MOSTTIMEGEAR:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_MOSTTIMEGEAR;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALDISTVALIDGEAR:                                {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALDISTVALIDGEAR;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALDISTWRONGGEAR:                                {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALDISTWRONGGEAR;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALDISTDOWNINDI:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALDISTDOWNINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALDISTUPINDI:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALDISTUPINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_AVGDISTWRONGINDI:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_AVGDISTWRONGINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_AVGDISTDOWNINDI:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_AVGDISTDOWNINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_AVGDISTUPINDI:                                     {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_AVGDISTUPINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALDISTWRONGGEARPER:                             {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALDISTWRONGGEARPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALDISTDOWNINDIPER:                              {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALDISTDOWNINDIPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALDISTUPINDIPER:                                {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALDISTUPINDIPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALTIMEVALIDGEAR:                                {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALTIMEVALIDGEAR;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALTIMEWRONGGEAR:                                {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALTIMEWRONGGEAR;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALTIMEDOWNINDI:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALTIMEDOWNINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALTIMEUPINDI:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALTIMEUPINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALTIMEWRONGGEARPER:                             {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALTIMEWRONGGEARPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALTIMEDOWNINDIPER:                              {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALTIMEDOWNINDIPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALTIMEUPINDIPER:                                {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALTIMEUPINDIPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALCOUNTWRONGGEAR:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALCOUNTWRONGGEAR;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALCOUNTDOWNINDI:                                {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALCOUNTDOWNINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALCOUNTUPINDI:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALCOUNTUPINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALCOUNTDOWNINDIPER:                             {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALCOUNTDOWNINDIPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALCOUNTUPINDIPER:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALCOUNTUPINDIPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_AVGCOUNTUPINDI:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_AVGCOUNTUPINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_AVGCOUNTDOWNINDI:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_AVGCOUNTDOWNINDI;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALTIMECORRECTGEARPER:                           {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALTIMECORRECTGEARPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_AVGGEARSHIFT:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_AVGGEARSHIFT;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_NOOFGEARSHIFT:                                     {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_NOOFGEARSHIFT;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_ODODISTPERTRIP:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_ODODISTPERTRIP;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOPSPEED:                                          {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOPSPEED;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_DRIVEINSTRATING:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_DRIVEINSTRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_DRIVECUMURATING:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_DRIVECUMURATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_SPEEDBAND1TIME:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_SPEEDBAND1TIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_SPEEDBAND1TIMEPER:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_SPEEDBAND1TIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_SPEEDBAND2TIME:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_SPEEDBAND2TIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_SPEEDBAND2TIMEPER:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_SPEEDBAND2TIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_SPEEDBAND3TIME:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_SPEEDBAND3TIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_SPEEDBAND3TIMEPER:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_SPEEDBAND3TIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_SPEEDBAND4TIME:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_SPEEDBAND4TIME;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_SPEEDBAND4TIMEPER:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_SPEEDBAND4TIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TRIPDIST:                                          {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TRIPDIST;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TRIPDURATION:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TRIPDURATION;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_AVGSPEED:                                          {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_AVGSPEED;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_AVGFUELECO:                                        {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_AVGFUELECO;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_OVERALLINSTRATING:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_OVERALLINSTRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_OVERALLCUMURATING:                                 {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_OVERALLCUMURATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_PERTIMEWITHOUTSEATBELT:                            {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_PERTIMEWITHOUTSEATBELT;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_PERTIMEWITHSEATBELT:                               {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_PERTIMEWITHSEATBELT;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_SEATBELTFACTOR:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_SEATBELTFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_NOOFTIMEWITHOUTSEATBELT:                           {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_NOOFTIMEWITHOUTSEATBELT;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_NOOFTIMEWITHSEATBELT:                              {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_NOOFTIMEWITHSEATBELT;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_NOOFTIMEWITHOUTSEATBELTPER:                        {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_NOOFTIMEWITHOUTSEATBELTPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_DOORCLOSETIMEPER:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_DOORCLOSETIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_DOOROPENTIMEPER:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_DOOROPENTIMEPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TIMEHIGHSPEEDCLTBRKPRESSEDPER:                     {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TIMEHIGHSPEEDCLTBRKPRESSEDPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TOTALTIMEHIGHSPEEDPER:                             {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TOTALTIMEHIGHSPEEDPER;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_SRSFACTOR:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_SRSFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TEABREAKFACTOR:                                    {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TEABREAKFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TRLFACTOR:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TRLFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TLLFACTOR:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TLLFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TBLFACTOR:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TBLFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TFLFACTOR:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TFLFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TPLFACTOR:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TPLFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_TRVLFACTOR:                                        {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_TRVLFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_BRKFLDFACTOR:                                      {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_BRKFLDFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_OILPRFACTOR:                                       {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_OILPRFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_WIFFACTOR:                                         {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_WIFFACTOR;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_VEHICLEHEALTH:                                     {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_VEHICLEHEALTH;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_SAFETYINSTRATING:                                  {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_SAFETYINSTRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::LASTTRIP_SAFETYCUMRATING:                                   {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_LASTTRIP_SAFETYCUMRATING;}break;
    case driveProTypeCollection::eSignalNames::Literal::TOTAL_COUNT:                                                {eHmiValue=EDriveNextSignalTypes::DRIVENEXT_SIG_TOTAL_COUNT;}break;
    default:
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, eProxyValue:%d, eHmiValue:%d", __FUNCTION__, static_cast<int>(eProxyValue), static_cast<int>(eHmiValue));
    }
        break;
    }
    return eHmiValue;
}


EDriveNextTripType CDriveNextModerator::convertDriveNextTripType(driveProTypeCollection::eTripType eTripType)
{
    EDriveNextTripType eDriveNextTripType = EDriveNextTripType::DRIVENEXT_TRIP_UNKNOWN;
    switch(eTripType)
    {
    case driveProTypeCollection::eTripType::TRIP_A:
    {
        eDriveNextTripType = EDriveNextTripType::DRIVENEXT_TRIP_A;
    }
        break;
    case driveProTypeCollection::eTripType::TRIP_B:
    {
        eDriveNextTripType = EDriveNextTripType::DRIVENEXT_TRIP_B;
    }
        break;
    case driveProTypeCollection::eTripType::OVERALL_TRIP:
    {
        eDriveNextTripType = EDriveNextTripType::DRIVENEXT_OVERALL_TRIP;
    }
        break;
    case driveProTypeCollection::eTripType::CURRENT_TRIP:
    {
        eDriveNextTripType = EDriveNextTripType::DRIVENEXT_CURRENT_TRIP;
    }
        break;
    case driveProTypeCollection::eTripType::LAST_TRIP:
    {
        eDriveNextTripType = EDriveNextTripType::DRIVENEXT_LAST_TRIP;
    }
        break;
    case driveProTypeCollection::eTripType::BEST_TRIP:
    {
        eDriveNextTripType = EDriveNextTripType::DRIVENEXT_BEST_TRIP;
    }
        break;
    case driveProTypeCollection::eTripType::ALL_TRIP:
    {
        eDriveNextTripType = EDriveNextTripType::DRIVENEXT_ALL_TRIP;
    }
        break;
    default:
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s tripType %d not handled", __FUNCTION__, static_cast<int>(eTripType));
    }
        break;
    }
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s : eDriveNextTripType %d", __FUNCTION__, static_cast<int>(eDriveNextTripType));
    return eDriveNextTripType;
}

bool CDriveNextModerator::convertDriveNextProxyTripType(EDriveNextTripType eTripType, driveProTypeCollection::eTripType &eProxyTripType)
{
    bool bStatus = true;
    switch (eTripType)
    {
    case EDriveNextTripType::DRIVENEXT_TRIP_A:
    {
        eProxyTripType = driveProTypeCollection::eTripType::TRIP_A;
    }
        break;
    case EDriveNextTripType::DRIVENEXT_TRIP_B:
    {
        eProxyTripType = driveProTypeCollection::eTripType::TRIP_B;
    }
        break;
    case EDriveNextTripType::DRIVENEXT_OVERALL_TRIP:
    {
        eProxyTripType = driveProTypeCollection::eTripType::OVERALL_TRIP;
    }
        break;
    case EDriveNextTripType::DRIVENEXT_CURRENT_TRIP:
    {
        eProxyTripType = driveProTypeCollection::eTripType::CURRENT_TRIP;
    }
        break;
    case EDriveNextTripType::DRIVENEXT_LAST_TRIP:
    {
        eProxyTripType = driveProTypeCollection::eTripType::LAST_TRIP;
    }
        break;
    case EDriveNextTripType::DRIVENEXT_BEST_TRIP:
    {
        eProxyTripType = driveProTypeCollection::eTripType::BEST_TRIP;
    }
        break;
    case EDriveNextTripType::DRIVENEXT_ALL_TRIP:
    {
        eProxyTripType = driveProTypeCollection::eTripType::ALL_TRIP;
    }
        break;
    default:
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eTripType %d not handled", __FUNCTION__, static_cast<int>(eTripType));
        bStatus = false;
    }
        break;
    }
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eProxyTripType %d", __FUNCTION__, static_cast<int>(eProxyTripType));
    return bStatus;
}

EDriveNextLogLevel CDriveNextModerator::convertDriveNextLogLevel(uint32_t uiLogLevel)
{
    EDriveNextLogLevel eDriveNextLogLevel = DRIVENEXT_LOG_LEVEL_UNKNOWN;
    switch(uiLogLevel)
    {
    case 0:
    {
        eDriveNextLogLevel = EDriveNextLogLevel::DRIVENEXT_LOG_LEVEL_0;
    }
        break;
    case 1:
    {
        eDriveNextLogLevel = EDriveNextLogLevel::DRIVENEXT_LOG_LEVEL_1;
    }
        break;
    case 2:
    {
        eDriveNextLogLevel = EDriveNextLogLevel::DRIVENEXT_LOG_LEVEL_2;
    }
        break;
    case 3:
    {
        eDriveNextLogLevel = EDriveNextLogLevel::DRIVENEXT_LOG_LEVEL_3;
    }
        break;
    default:
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s uiLogLevel %d not handled", __FUNCTION__, uiLogLevel);
    }
        break;
    }
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s : eDriveNextLogLevel %d", __FUNCTION__, static_cast<int>(eDriveNextLogLevel));
    return eDriveNextLogLevel;
}

bool CDriveNextModerator::convertDriveNextProxyLogLevel(EDriveNextLogLevel eDriveNextLogLevel, uint32_t &uiLogLevel)
{
    bool bStatus = true;
    switch (eDriveNextLogLevel)
    {
    case EDriveNextLogLevel::DRIVENEXT_LOG_LEVEL_0:
    {
        uiLogLevel = 0;
    }
        break;
    case EDriveNextLogLevel::DRIVENEXT_LOG_LEVEL_1:
    {
        uiLogLevel = 1;
    }
        break;
    case EDriveNextLogLevel::DRIVENEXT_LOG_LEVEL_2:
    {
        uiLogLevel = 2;
    }
        break;
    case EDriveNextLogLevel::DRIVENEXT_LOG_LEVEL_3:
    {
        uiLogLevel = 3;
    }
        break;
    default:
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eDriveNextLogLevel %d not handled", __FUNCTION__, static_cast<int>(eDriveNextLogLevel));
        bStatus = false;
    }
        break;
    }
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s uiLogLevel %d", __FUNCTION__, uiLogLevel);
    return bStatus;
}

EDriveNextLoggingType CDriveNextModerator::convertDriveNextLoggingType(driveProTypeCollection::eLoggingType eLoggingType)
{
    EDriveNextLoggingType eDriveNextLoggingType = EDriveNextLoggingType::DRIVENEXT_LOG_TYPE_UNKNOWN;
    switch(eLoggingType)
    {
    case driveProTypeCollection::eLoggingType::LOGGING_INTERNAL:
    {
        eDriveNextLoggingType = EDriveNextLoggingType::DRIVENEXT_LOG_TYPE_INTERNAL;
    }
        break;
    case driveProTypeCollection::eLoggingType::LOGGING_USB:
    {
        eDriveNextLoggingType = EDriveNextLoggingType::DRIVENEXT_LOG_TYPE_USB;
    }
        break;
    default:
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eLoggingType %d not handled", __FUNCTION__, static_cast<int>(eLoggingType));
    }
        break;
    }
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s : eDriveNextLoggingType %d", __FUNCTION__, static_cast<int>(eDriveNextLoggingType));
    return eDriveNextLoggingType;
}

bool CDriveNextModerator::convertDriveNextProxyLoggingType(EDriveNextLoggingType eLoggingType, driveProTypeCollection::eLoggingType &eProxtLoggingType)
{
    bool bStatus = true;
    switch (eLoggingType)
    {
    case EDriveNextLoggingType::DRIVENEXT_LOG_TYPE_INTERNAL:
    {
        eProxtLoggingType = driveProTypeCollection::eLoggingType::LOGGING_INTERNAL;
    }
        break;
    case EDriveNextLoggingType::DRIVENEXT_LOG_TYPE_USB:
    {
        eProxtLoggingType = driveProTypeCollection::eLoggingType::LOGGING_USB;
    }
        break;
    default:
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eLoggingType %d not handled", __FUNCTION__, static_cast<int>(eLoggingType));
        bStatus = false;
    }
        break;
    }
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eProxtLoggingType %d", __FUNCTION__, static_cast<int>(eProxtLoggingType));
    return bStatus;
}

EDriveNextDistanceUnitType CDriveNextModerator::convertDriveNextDistUnitType(driveProTypeCollection::eDistUnit eProxtDistUnitType)
{
    EDriveNextDistanceUnitType eDistUnitType = EDriveNextDistanceUnitType::DRIVENEXT_DIST_TYPE_UNKNOWN;
    switch(eProxtDistUnitType)
    {
    case driveProTypeCollection::eDistUnit::KILO_METER:
    {
        eDistUnitType = EDriveNextDistanceUnitType::DRIVENEXT_DIST_TYPE_KM;
    }
        break;
    case driveProTypeCollection::eDistUnit::MILES:
    {
        eDistUnitType = EDriveNextDistanceUnitType::DRIVENEXT_DIST_TYPE_MILES;
    }
        break;
    default:
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eProxtDistUnitType %d not handled", __FUNCTION__, static_cast<int>(eProxtDistUnitType));
    }
        break;
    }
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s : eDistUnitType %d", __FUNCTION__, static_cast<int>(eDistUnitType));
    return eDistUnitType;
}

bool CDriveNextModerator::convertDriveNextProxyDistUnitType(EDriveNextDistanceUnitType eDistUnitType, driveProTypeCollection::eDistUnit &eProxtDistUnitType)
{
    bool bStatus = true;
    switch (eDistUnitType)
    {
    case EDriveNextDistanceUnitType::DRIVENEXT_DIST_TYPE_KM:
    {
        eProxtDistUnitType = driveProTypeCollection::eDistUnit::KILO_METER;
    }
        break;
    case EDriveNextDistanceUnitType::DRIVENEXT_DIST_TYPE_MILES:
    {
        eProxtDistUnitType = driveProTypeCollection::eDistUnit::MILES;
    }
        break;
    default:
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eDistUnitType %d not handled", __FUNCTION__, static_cast<int>(eDistUnitType));
        bStatus = false;
    }
        break;
    }
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eProxtDistUnitType %d", __FUNCTION__, static_cast<int>(eProxtDistUnitType));
    return bStatus;
}

EDriveNextFuelUnitType CDriveNextModerator::convertDriveNextFuelUnitType(driveProTypeCollection::eFuelUnit eProxtFuelUnitType)
{
    EDriveNextFuelUnitType eFuelUnitType = EDriveNextFuelUnitType::DRIVENEXT_FUEL_TYPE_UNKNOWN;
    switch(eProxtFuelUnitType)
    {
    case driveProTypeCollection::eFuelUnit::KM_PER_LITRE:
    {
        eFuelUnitType = EDriveNextFuelUnitType::DRIVENEXT_FUEL_TYPE_KM_PER_LITRE;
    }
        break;
    case driveProTypeCollection::eFuelUnit::LITRE_PER_HUNDRED_KM:
    {
        eFuelUnitType = EDriveNextFuelUnitType::DRIVENEXT_FUEL_TYPE_LITRE_PER_HUNDRED_KM;
    }
        break;
    case driveProTypeCollection::eFuelUnit::MPG:
    {
        eFuelUnitType = EDriveNextFuelUnitType::DRIVENEXT_FUEL_TYPE_MPG;
    }
        break;
    case driveProTypeCollection::eFuelUnit::SNA:
    {
        eFuelUnitType = EDriveNextFuelUnitType::DRIVENEXT_FUEL_TYPE_SNA;
    }
        break;
    default:
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eProxtFuelUnitType %d not handled", __FUNCTION__, static_cast<int>(eProxtFuelUnitType));
    }
        break;
    }
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s : eFuelUnitType %d", __FUNCTION__, static_cast<int>(eFuelUnitType));
    return eFuelUnitType;
}

bool CDriveNextModerator::convertDriveNextProxyFuelUnitType(EDriveNextFuelUnitType eFuelUnitType, driveProTypeCollection::eFuelUnit &eProxtFuelUnitType)
{
    bool bStatus = true;
    switch (eFuelUnitType)
    {
    case EDriveNextFuelUnitType::DRIVENEXT_FUEL_TYPE_KM_PER_LITRE:
    {
        eProxtFuelUnitType = driveProTypeCollection::eFuelUnit::KM_PER_LITRE;
    }
        break;
    case EDriveNextFuelUnitType::DRIVENEXT_FUEL_TYPE_LITRE_PER_HUNDRED_KM:
    {
        eProxtFuelUnitType = driveProTypeCollection::eFuelUnit::LITRE_PER_HUNDRED_KM;
    }
        break;
    case EDriveNextFuelUnitType::DRIVENEXT_FUEL_TYPE_MPG:
    {
        eProxtFuelUnitType = driveProTypeCollection::eFuelUnit::MPG;
    }
        break;
    case EDriveNextFuelUnitType::DRIVENEXT_FUEL_TYPE_SNA:
    {
        eProxtFuelUnitType = driveProTypeCollection::eFuelUnit::SNA;
    }
        break;
    case EDriveNextFuelUnitType::DRIVENEXT_FUEL_TYPE_UNKNOWN:
    default:
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eFuelUnitType %d not handled", __FUNCTION__, static_cast<int>(eFuelUnitType));
        bStatus = false;
    }
        break;
    }
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eProxtFuelUnitType %d", __FUNCTION__, static_cast<int>(eProxtFuelUnitType));
    return bStatus;
}

EDriveNextSignalErrorTypes CDriveNextModerator::convertDriveNextSignalErrorType(driveProTypeCollection::eDpErrorCode eProxySignalErrorType)
{
    EDriveNextSignalErrorTypes eSignalErrorType = EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_UNKNOWN;
    switch(eProxySignalErrorType)
    {
    case driveProTypeCollection::eDpErrorCode::ERROR_CONFIGURATION_FILE_PATH_NOT_FOUND:
    {
        eSignalErrorType = EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_CONFIGURATION_FILE_PATH_NOT_FOUND;
    }
        break;
    case driveProTypeCollection::eDpErrorCode::ERROR_TRIP_HISTORY_FILE_PATHIN_VALID:
    {
        eSignalErrorType = EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_TRIP_HISTORY_FILE_PATHIN_VALID;
    }
        break;
    case driveProTypeCollection::eDpErrorCode::ERROR_CONFIGURATION_FILE_INVALID:
    {
        eSignalErrorType = EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_CONFIGURATION_FILE_INVALID;
    }
        break;
    case driveProTypeCollection::eDpErrorCode::ERROR_TRIP_HISTORY_FILE_INVALID:
    {
        eSignalErrorType = EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_TRIP_HISTORY_FILE_INVALID;
    }
        break;
    case driveProTypeCollection::eDpErrorCode::ERROR_VALUE_NOT_IN_RANGE:
    {
        eSignalErrorType = EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_VALUE_NOT_IN_RANGE;
    }
        break;
    case driveProTypeCollection::eDpErrorCode::ERROR_VALUE_ABOVE_RANGE:
    {
        eSignalErrorType = EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_VALUE_ABOVE_RANGE;
    }
        break;
    case driveProTypeCollection::eDpErrorCode::ERROR_VALUE_BELOW_RANGE:
    {
        eSignalErrorType = EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_VALUE_BELOW_RANGE;
    }
        break;
    case driveProTypeCollection::eDpErrorCode::ERROR_SIGNAL_VALUE_NOT_SET:
    {
        eSignalErrorType = EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_SIGNAL_VALUE_NOT_SET;
    }
        break;
    case driveProTypeCollection::eDpErrorCode::ERROR_SIGNAL_VALUE_NOT_AVAILABLE:
    {
        eSignalErrorType = EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_SIGNAL_VALUE_NOT_AVAILABLE;
    }
        break;
    case driveProTypeCollection::eDpErrorCode::ERROR_DIVIDEBYZERO:
    {
        eSignalErrorType = EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_DIVIDEBYZERO;
    }
        break;
    case driveProTypeCollection::eDpErrorCode::ERROR_OVERFLOW:
    {
        eSignalErrorType = EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_OVERFLOW;
    }
        break;
    case driveProTypeCollection::eDpErrorCode::ERROR_JSON_INVALID:
    {
        eSignalErrorType = EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_JSON_INVALID;
    }
        break;
    case driveProTypeCollection::eDpErrorCode::ERROR_DATA_INCOMPLETE:
    {
        eSignalErrorType = EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_DATA_INCOMPLETE;
    }
        break;
    case driveProTypeCollection::eDpErrorCode::ERROR_OTHER:
    {
        eSignalErrorType = EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_OTHER;
    }
        break;
    case driveProTypeCollection::eDpErrorCode::ERROR_TRIPID_NOT_FOUND:
    {
        eSignalErrorType = EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_TRIPID_NOT_FOUND;
    }
        break;
    case driveProTypeCollection::eDpErrorCode::ERROR_STATE_PERMISSION_DENIED:
    {
        eSignalErrorType = EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_STATE_PERMISSION_DENIED;
    }
        break;
    case driveProTypeCollection::eDpErrorCode::ERROR_CANNOT_CREATE_USER_DIRECTORY:
    {
        eSignalErrorType = EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_CANNOT_CREATE_USER_DIRECTORY;
    }
        break;
    case driveProTypeCollection::eDpErrorCode::ERROR_EXCEPTION:
    {
        eSignalErrorType = EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_EXCEPTION;
    }
        break;
    case driveProTypeCollection::eDpErrorCode::ERROR_TRIP_NOT_RUNNING:
    {
        eSignalErrorType = EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_TRIP_NOT_RUNNING;
    }
        break;
    case driveProTypeCollection::eDpErrorCode::ERROR_TRIP_DISTANCE_THRESH:
    {
        eSignalErrorType = EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_TRIP_DISTANCE_THRESH;
    }
        break;
    case driveProTypeCollection::eDpErrorCode::ERROR_LIBRARY_NOT_INITIALIZED:
    {
        eSignalErrorType = EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_LIBRARY_NOT_INITIALIZED;
    }
        break;
    case driveProTypeCollection::eDpErrorCode::ERROR_AMT_VEHICLE:
    {
        eSignalErrorType = EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_AMT_VEHICLE;
    }
        break;
    case driveProTypeCollection::eDpErrorCode::SUCCESS:
    {
        eSignalErrorType = EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_SUCCESS;
    }
        break;
    case driveProTypeCollection::eDpErrorCode::UNKNOWN:
    {
        //eSignalErrorType = EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_UNKNOWN;
        //Do Nothing!
    }
        break;
    default:
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eProxySignalErrorType %d not handled", __FUNCTION__, static_cast<int>(eProxySignalErrorType));
    }
        break;
    }
    return eSignalErrorType;
}

bool CDriveNextModerator::convertDriveNextProxySignalErrorType(EDriveNextSignalErrorTypes eSignalErrorType, driveProTypeCollection::eDpErrorCode &eProxySignalErrorType)
{
    bool bStatus = true;
    switch (eSignalErrorType)
    {
    case EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_CONFIGURATION_FILE_PATH_NOT_FOUND:
    {
        eProxySignalErrorType = driveProTypeCollection::eDpErrorCode::ERROR_CONFIGURATION_FILE_PATH_NOT_FOUND;
    }
        break;
    case EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_TRIP_HISTORY_FILE_PATHIN_VALID:
    {
        eProxySignalErrorType = driveProTypeCollection::eDpErrorCode::ERROR_TRIP_HISTORY_FILE_PATHIN_VALID;
    }
        break;
    case EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_CONFIGURATION_FILE_INVALID:
    {
        eProxySignalErrorType = driveProTypeCollection::eDpErrorCode::ERROR_CONFIGURATION_FILE_INVALID;
    }
        break;
    case EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_TRIP_HISTORY_FILE_INVALID:
    {
        eProxySignalErrorType = driveProTypeCollection::eDpErrorCode::ERROR_TRIP_HISTORY_FILE_INVALID;
    }
        break;
    case EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_VALUE_NOT_IN_RANGE:
    {
        eProxySignalErrorType = driveProTypeCollection::eDpErrorCode::ERROR_VALUE_NOT_IN_RANGE;
    }
        break;
    case EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_VALUE_ABOVE_RANGE:
    {
        eProxySignalErrorType = driveProTypeCollection::eDpErrorCode::ERROR_VALUE_ABOVE_RANGE;
    }
        break;
    case EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_VALUE_BELOW_RANGE:
    {
        eProxySignalErrorType = driveProTypeCollection::eDpErrorCode::ERROR_VALUE_BELOW_RANGE;
    }
        break;
    case EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_SIGNAL_VALUE_NOT_SET:
    {
        eProxySignalErrorType = driveProTypeCollection::eDpErrorCode::ERROR_SIGNAL_VALUE_NOT_SET;
    }
        break;
    case EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_SIGNAL_VALUE_NOT_AVAILABLE:
    {
        eProxySignalErrorType = driveProTypeCollection::eDpErrorCode::ERROR_SIGNAL_VALUE_NOT_AVAILABLE;
    }
        break;
    case EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_DIVIDEBYZERO:
    {
        eProxySignalErrorType = driveProTypeCollection::eDpErrorCode::ERROR_DIVIDEBYZERO;
    }
        break;
    case EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_OVERFLOW:
    {
        eProxySignalErrorType = driveProTypeCollection::eDpErrorCode::ERROR_OVERFLOW;
    }
        break;
    case EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_JSON_INVALID:
    {
        eProxySignalErrorType = driveProTypeCollection::eDpErrorCode::ERROR_JSON_INVALID;
    }
        break;
    case EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_DATA_INCOMPLETE:
    {
        eProxySignalErrorType = driveProTypeCollection::eDpErrorCode::ERROR_DATA_INCOMPLETE;
    }
        break;
    case EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_OTHER:
    {
        eProxySignalErrorType = driveProTypeCollection::eDpErrorCode::ERROR_OTHER;
    }
        break;
    case EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_TRIPID_NOT_FOUND:
    {
        eProxySignalErrorType = driveProTypeCollection::eDpErrorCode::ERROR_TRIPID_NOT_FOUND;
    }
        break;
    case EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_STATE_PERMISSION_DENIED:
    {
        eProxySignalErrorType = driveProTypeCollection::eDpErrorCode::ERROR_STATE_PERMISSION_DENIED;
    }
        break;
    case EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_CANNOT_CREATE_USER_DIRECTORY:
    {
        eProxySignalErrorType = driveProTypeCollection::eDpErrorCode::ERROR_CANNOT_CREATE_USER_DIRECTORY;
    }
        break;
    case EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_EXCEPTION:
    {
        eProxySignalErrorType = driveProTypeCollection::eDpErrorCode::ERROR_EXCEPTION;
    }
        break;
    case EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_TRIP_NOT_RUNNING:
    {
        eProxySignalErrorType = driveProTypeCollection::eDpErrorCode::ERROR_TRIP_NOT_RUNNING;
    }
        break;
    case EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_TRIP_DISTANCE_THRESH:
    {
        eProxySignalErrorType = driveProTypeCollection::eDpErrorCode::ERROR_TRIP_DISTANCE_THRESH;
    }
        break;
    case EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_LIBRARY_NOT_INITIALIZED:
    {
        eProxySignalErrorType = driveProTypeCollection::eDpErrorCode::ERROR_LIBRARY_NOT_INITIALIZED;
    }
        break;
    case EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_AMT_VEHICLE:
    {
        eProxySignalErrorType = driveProTypeCollection::eDpErrorCode::ERROR_AMT_VEHICLE;
    }
        break;
    case EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_SUCCESS:
    {
        eProxySignalErrorType = driveProTypeCollection::eDpErrorCode::SUCCESS;
    }
        break;
    case EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_UNKNOWN:
    {
        eProxySignalErrorType = driveProTypeCollection::eDpErrorCode::UNKNOWN;
    }
        break;
    default:
    {
        eProxySignalErrorType = driveProTypeCollection::eDpErrorCode::UNKNOWN;
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eSignalErrorType %d not handled", __FUNCTION__, static_cast<int>(eSignalErrorType));
        bStatus = false;
    }
        break;
    }
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s eProxySignalErrorType %d", __FUNCTION__, static_cast<int>(eProxySignalErrorType));
    return bStatus;
}
