#include "StatisticsRepository.h"

#include <stdio.h>

#include "../database/Database.h"

bool StatisticsRepository::loadRecentEvents(
    StatisticsEventView (&events)[MaxEvents],
    uint8_t& eventCount
)
{
    eventCount = 0;

    LittleDB::TableIterator<Statistics> iterator =
        Database::statistics().iterator();

    if (iterator.begin() != LittleDB::Result::Ok)
    {
        return false;
    }

    while (iterator.valid())
    {
        const LittleDB::Record<Statistics>& record =
            iterator.record();

        StatisticsEventView event;

        mapEvent(
            record.data,
            event
        );

        if (eventCount < MaxEvents)
        {
            events[eventCount] = event;

            eventCount++;
        }
        else
        {
            /*
             * Уже есть 4 записи.
             * Сдвигаем их влево и добавляем
             * более новую запись в конец.
             */
            events[0] = events[1];
            events[1] = events[2];
            events[2] = events[3];
            events[3] = event;
        }

        if (!iterator.next())
        {
            break;
        }
    }

    iterator.end();

    return true;
}

void StatisticsRepository::mapEvent(
    const Statistics& statistics,
    StatisticsEventView& event
)
{
    formatTime(
        statistics.timestamp,
        event.time
    );

    event.type =
        statistics.type;

    event.state =
        statistics.state;

    event.synced =
        statistics.synced;
}

void StatisticsRepository::formatTime(
    uint32_t timestamp,
    char* buffer
)
{
    /*
     * Сейчас timestamp хранится как millis().
     *
     * Для отображения преобразуем его
     * в HH:MM:SS.
     *
     * Позже TimeManager перейдёт на реальное
     * время, а формат отображения здесь
     * останется тем же.
     */

    uint32_t totalSeconds =
        timestamp / 1000;

    uint32_t hours =
        (totalSeconds / 3600) % 24;

    uint32_t minutes =
        (totalSeconds / 60) % 60;

    uint32_t seconds =
        totalSeconds % 60;

    snprintf(
        buffer,
        9,
        "%02lu:%02lu:%02lu",
        static_cast<unsigned long>(hours),
        static_cast<unsigned long>(minutes),
        static_cast<unsigned long>(seconds)
    );
}